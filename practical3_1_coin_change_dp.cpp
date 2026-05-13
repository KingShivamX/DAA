/*
 * Coin Change — Minimum Coins (Dynamic Programming)
 *
 * ---------------------------------------------------------------
 * Find the minimum number of coins needed to make a target amount.
 * Uses bottom-up DP:
 *   dp[i] = minimum coins needed to make amount i
 *
 * Base case : dp[0] = 0  (zero coins to make amount 0)
 * Transition: dp[i] = min(dp[i - coin] + 1) for all valid coins
 *
 * Time  : O(n * amount)  — n = number of denominations
 * Space : O(amount)      — DP table
 *
 * This guarantees the optimal answer for ANY set of denominations,
 * unlike the greedy approach (practical2_2).
 * ---------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

const int INF = 1e9;

// ---- Core Algorithm --------------------------------------------------

int minCoinsDP(const vector<int>& coins, int amount) {
    // dp[i] = min coins to form amount i; start with "impossible" (INF)
    vector<int> dp(amount + 1, INF);
    dp[0] = 0;

    for (int i = 1; i <= amount; i++) {
        for (int coin : coins) {
            // Only use this coin if it fits and the sub-problem is solvable
            if (coin <= i && dp[i - coin] != INF)
                dp[i] = min(dp[i], dp[i - coin] + 1);
        }
    }

    return (dp[amount] == INF) ? -1 : dp[amount];
}

// ---- Main ------------------------------------------------------------

int main() {
    int n, target;

    cout << "Enter number of denominations : ";
    cin >> n;

    vector<int> coins(n);
    cout << "Enter denominations           : ";
    for (int i = 0; i < n; i++)
        cin >> coins[i];

    cout << "Enter target amount           : ";
    cin >> target;

    auto start = chrono::high_resolution_clock::now();

    int result = minCoinsDP(coins, target);

    auto stop     = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    if (result != -1)
        cout << "\nMinimum coins required : " << result << endl;
    else
        cout << "\nAmount cannot be formed with the given coins." << endl;

    cout << "Time                   : " << dur << " microseconds" << endl;

    return 0;
}
