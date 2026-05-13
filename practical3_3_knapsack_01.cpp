/*
 * 0/1 Knapsack Problem (Dynamic Programming)
 *
 * ---------------------------------------------------------------
 * Select items (each used at most once) to maximise total value
 * without exceeding the knapsack's weight capacity.
 *
 * dp[i][w] = maximum value achievable using the first i items
 *            with a weight limit of w.
 *
 * Transition:
 *   If item i fits (weight[i] <= w):
 *     dp[i][w] = max(dp[i-1][w],  value[i] + dp[i-1][w - weight[i]])
 *   Else:
 *     dp[i][w] = dp[i-1][w]
 *
 * Time  : O(n * W)  — n = items, W = capacity
 * Space : O(n * W)  — 2D DP table
 *         (Reducible to O(W) with a 1D rolling array)
 * ---------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

// ---- Core Algorithm --------------------------------------------------

void knapsack01(const vector<int>& weights, const vector<int>& values,
                int n, int capacity) {

    // dp[i][w] = best value using items 1..i with weight limit w
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            // Option 1: skip item i
            dp[i][w] = dp[i - 1][w];

            // Option 2: include item i (only if it fits)
            if (weights[i - 1] <= w) {
                int includeValue = values[i - 1] + dp[i - 1][w - weights[i - 1]];
                dp[i][w] = max(dp[i][w], includeValue);
            }
        }
    }

    cout << "\nMaximum value : " << dp[n][capacity] << endl;

    // Backtrack through the table to identify which items were selected
    cout << "Items selected:" << endl;
    int w = capacity;
    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            cout << "  Item " << i
                 << "  (weight=" << weights[i - 1]
                 << ", value="   << values[i - 1] << ")" << endl;
            w -= weights[i - 1];
        }
    }
}

// ---- Main ------------------------------------------------------------

int main() {
    int n, capacity;

    cout << "Enter number of items   : ";
    cin >> n;
    cout << "Enter knapsack capacity : ";
    cin >> capacity;

    vector<int> weights(n), values(n);
    cout << "Enter weight and value for each item:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  Item " << i + 1 << " (weight value): ";
        cin >> weights[i] >> values[i];
    }

    auto start = chrono::high_resolution_clock::now();

    knapsack01(weights, values, n, capacity);

    auto stop     = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    cout << "Time          : " << dur << " microseconds" << endl;

    return 0;
}
