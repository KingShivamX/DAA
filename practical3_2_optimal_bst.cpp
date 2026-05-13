/*
 * Optimal Binary Search Tree (Dynamic Programming)
 *
 * ---------------------------------------------------------------
 * Given n keys with successful search probabilities p[1..n] and
 * n+1 dummy keys with unsuccessful search probabilities q[0..n],
 * find the BST arrangement that minimises expected search cost.
 *
 * dp[i][j]     = minimum expected cost for keys i through j
 * weight[i][j] = total probability mass of keys i..j plus dummies
 * root[i][j]   = optimal root for subproblem keys i..j
 *
 * Time  : O(n^3)  — three nested loops over all subproblems
 * Space : O(n^2)  — dp, weight, and root tables
 * ---------------------------------------------------------------
 */

#include <iostream>
#include <chrono>

using namespace std;

const int MAX_KEYS = 20;

// ---- Core Algorithm --------------------------------------------------

void optimalBST(float p[], float q[], int n) {
    float dp[MAX_KEYS + 2][MAX_KEYS + 2];
    float weight[MAX_KEYS + 2][MAX_KEYS + 2];
    int   root[MAX_KEYS + 2][MAX_KEYS + 2];

    // Base case: subtree with no keys (only a dummy key)
    for (int i = 1; i <= n + 1; i++) {
        dp[i][i - 1]     = q[i - 1];
        weight[i][i - 1] = q[i - 1];
    }

    // Build table for increasing chain lengths
    for (int len = 1; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;

            dp[i][j]     = 1e9;  // start with "infinity"
            weight[i][j] = weight[i][j - 1] + p[j] + q[j];

            // Try every key r as the root of subproblem keys i..j
            for (int r = i; r <= j; r++) {
                float cost = dp[i][r - 1] + dp[r + 1][j] + weight[i][j];
                if (cost < dp[i][j]) {
                    dp[i][j]   = cost;
                    root[i][j] = r;
                }
            }
        }
    }

    cout << "\nMinimum expected search cost : " << dp[1][n]   << endl;
    cout << "Root of the optimal BST      : Key " << root[1][n] << endl;
}

// ---- Main ------------------------------------------------------------

int main() {
    int n;
    cout << "Enter number of keys: ";
    cin >> n;

    float p[MAX_KEYS + 1], q[MAX_KEYS + 1];

    cout << "Enter successful search probabilities p[1] to p[" << n << "]: ";
    for (int i = 1; i <= n; i++)
        cin >> p[i];

    cout << "Enter unsuccessful search probabilities q[0] to q[" << n << "]: ";
    for (int i = 0; i <= n; i++)
        cin >> q[i];

    auto start = chrono::high_resolution_clock::now();

    optimalBST(p, q, n);

    auto stop     = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    cout << "Time                         : " << dur << " microseconds" << endl;

    return 0;
}
