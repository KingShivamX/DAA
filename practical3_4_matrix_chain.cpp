// Practical 3.4 - Matrix Chain Multiplication (Dynamic Programming)
// Find the optimal parenthesization that minimizes total scalar multiplications.
// Time: O(n^3) | dp[i][j] = min cost to multiply matrices i through j.

#include <bits/stdc++.h>
using namespace std;

void printParens(vector<vector<int>>& s, int i, int j, char& name) {
    if (i == j) { cout << name++; return; }
    cout << "(";
    printParens(s, i, s[i][j], name);
    printParens(s, s[i][j] + 1, j, name);
    cout << ")";
}

void matrixChain(int dims[], int n) {
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> s(n + 1, vector<int>(n + 1, 0));

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + dims[i - 1] * dims[k] * dims[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    s[i][j]  = k;
                }
            }
        }
    }

    cout << "Min multiplications: " << dp[1][n] << "\n";
    cout << "Optimal order: ";
    char name = 'A';
    printParens(s, 1, n, name);
    cout << "\n";
}

int main() {
    int n;
    cout << "Enter number of matrices: ";
    cin >> n;

    int* dims = new int[n + 1];
    cout << "Enter " << n + 1 << " dimensions: ";
    for (int i = 0; i <= n; i++) cin >> dims[i];

    matrixChain(dims, n);

    delete[] dims;
    return 0;
}
