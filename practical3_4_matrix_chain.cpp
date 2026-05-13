/*
 * Matrix Chain Multiplication (Dynamic Programming)
 *
 * ---------------------------------------------------------------
 * Find the optimal parenthesisation of a chain of matrices to
 * minimise the total number of scalar multiplications.
 *
 * Input : dims[0..n] where matrix i has size dims[i] x dims[i+1]
 *
 * dp[i][j]    = minimum multiplications to compute matrices i..j
 * split[i][j] = optimal split point k for subproblem i..j
 *
 * Cost of multiplying (i..k) * (k+1..j):
 *   dp[i][k] + dp[k+1][j] + dims[i-1] * dims[k] * dims[j]
 *
 * Time  : O(n^3)  — three nested loops
 * Space : O(n^2)  — dp and split tables
 * ---------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

const int INF = 1e9;

// ---- Helpers ---------------------------------------------------------

// Recursively print the optimal parenthesisation
void printOptimalParens(const vector<vector<int>>& split, int i, int j, char& name) {
    if (i == j) {
        // Single matrix: print its label (A, B, C, ...)
        cout << name++;
        return;
    }
    cout << "(";
    printOptimalParens(split, i,               split[i][j],     name);
    printOptimalParens(split, split[i][j] + 1, j,               name);
    cout << ")";
}

// ---- Core Algorithm --------------------------------------------------

void matrixChainOrder(const vector<int>& dims, int n) {
    // dp[i][j]    = min cost for matrices i through j (1-indexed)
    // split[i][j] = best split point k
    vector<vector<int>> dp(n + 1,    vector<int>(n + 1, 0));
    vector<vector<int>> split(n + 1, vector<int>(n + 1, 0));

    // len = length of chain being considered (start from 2)
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = INF;

            // Try every possible split point k between i and j
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j]
                         + dims[i - 1] * dims[k] * dims[j];

                if (cost < dp[i][j]) {
                    dp[i][j]    = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    cout << "\nMinimum scalar multiplications : " << dp[1][n] << endl;

    cout << "Optimal parenthesisation       : ";
    char name = 'A';
    printOptimalParens(split, 1, n, name);
    cout << endl;
}

// ---- Main ------------------------------------------------------------

int main() {
    int n;
    cout << "Enter number of matrices: ";
    cin >> n;

    // Need n+1 dimensions: dims[0]xdims[1], dims[1]xdims[2], ...
    vector<int> dims(n + 1);
    cout << "Enter " << n + 1 << " dimensions (d0 d1 ... d" << n << "): ";
    for (int i = 0; i <= n; i++)
        cin >> dims[i];

    auto start = chrono::high_resolution_clock::now();

    matrixChainOrder(dims, n);

    auto stop     = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    cout << "Time                           : " << dur << " microseconds" << endl;

    return 0;
}
