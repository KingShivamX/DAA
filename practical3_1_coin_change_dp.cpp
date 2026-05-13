// Practical 3.1 - Coin Change (Dynamic Programming)
// dp[i] = minimum coins needed to make amount i. Fill bottom-up for all amounts.
// Time: O(n * amount) | Unlike greedy, works for any coin system.

#include <bits/stdc++.h>
using namespace std;

int minCoins(int coins[], int n, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < n; j++) {
            if (coins[j] <= i && dp[i - coins[j]] != INT_MAX)
                dp[i] = min(dp[i], dp[i - coins[j]] + 1);
        }
    }

    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

int main() {
    int n, target;
    cout << "Enter number of denominations: ";
    cin >> n;

    int* coins = new int[n];
    cout << "Enter denominations: ";
    for (int i = 0; i < n; i++) cin >> coins[i];

    cout << "Enter target amount: ";
    cin >> target;

    int result = minCoins(coins, n, target);
    if (result != -1)
        cout << "Minimum coins: " << result << "\n";
    else
        cout << "Cannot form amount.\n";

    delete[] coins;
    return 0;
}
