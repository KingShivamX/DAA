// Practical 3.2 - Optimal Binary Search Tree (Dynamic Programming)
// Find the BST structure that minimizes expected search cost given key probabilities.
// Time: O(n^3) | Uses DP over all subtrees of increasing length.

#include <bits/stdc++.h>
using namespace std;

const int MAX = 20;

void findOptimalBST(float p[], float q[], int n) {
    float cost[MAX][MAX];   // cost[i][j] = expected cost of subtree i..j
    float w[MAX][MAX];      // w[i][j] = sum of probabilities for subtree i..j
    int   root[MAX][MAX];   // root[i][j] = root of optimal subtree i..j

    // Base case: empty subtrees
    for (int i = 1; i <= n + 1; i++) {
        cost[i][i - 1] = q[i - 1];
        w[i][i - 1]    = q[i - 1];
    }

    // Fill for increasing subtree lengths
    for (int len = 1; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            cost[i][j] = 1e9;
            w[i][j]    = w[i][j - 1] + p[j] + q[j];

            for (int r = i; r <= j; r++) {
                float c = cost[i][r - 1] + cost[r + 1][j] + w[i][j];
                if (c < cost[i][j]) {
                    cost[i][j] = c;
                    root[i][j] = r;
                }
            }
        }
    }

    cout << "Min expected search cost: " << cost[1][n] << "\n";
    cout << "Root of optimal BST: " << root[1][n] << "\n";
}

int main() {
    int n;
    cout << "Enter number of keys: ";
    cin >> n;

    float p[MAX], q[MAX];
    cout << "Enter successful search probabilities (p1 to p" << n << "): ";
    for (int i = 1; i <= n; i++) cin >> p[i];

    cout << "Enter unsuccessful search probabilities (q0 to q" << n << "): ";
    for (int i = 0; i <= n; i++) cin >> q[i];

    findOptimalBST(p, q, n);
    return 0;
}
