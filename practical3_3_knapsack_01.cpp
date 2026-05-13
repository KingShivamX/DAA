// Practical 3.3 - 0/1 Knapsack (Dynamic Programming)
// dp[i][w] = max value using first i items with weight capacity w.
// Each item is either taken (1) or not (0). Time: O(n * W)

#include <bits/stdc++.h>
using namespace std;

void knapsack(int weights[], int values[], int n, int W) {
    // Build DP table bottom-up
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (weights[i - 1] <= w)
                dp[i][w] = max(dp[i - 1][w], values[i - 1] + dp[i - 1][w - weights[i - 1]]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    cout << "Max profit: " << dp[n][W] << "\n";

    // Traceback to find which items were included
    cout << "Items included: ";
    int w = W;
    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            cout << i << " ";
            w -= weights[i - 1];
        }
    }
    cout << "\n";
}

int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;
    cout << "Enter knapsack capacity: ";
    cin >> W;

    int* weights = new int[n];
    int* values  = new int[n];
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << " weight value: ";
        cin >> weights[i] >> values[i];
    }

    knapsack(weights, values, n, W);

    delete[] weights;
    delete[] values;
    return 0;
}
