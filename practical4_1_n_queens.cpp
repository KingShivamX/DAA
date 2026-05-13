/*
 * N-Queens Problem (Backtracking)
 *
 * ---------------------------------------------------------------
 * Place N queens on an NxN chessboard so that no two queens
 * attack each other. Queens attack in the same row, column, or
 * diagonal.
 *
 * Strategy: Place queens column by column. For each column, try
 *   every row. If the placement is safe, recurse to the next column.
 *   If no safe row exists, backtrack.
 *
 * Time  : O(n!)  worst case — in practice much faster due to pruning
 * Space : O(n^2) — board storage
 *         O(n)   — recursion stack depth
 * ---------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

// ---- Safety Check ----------------------------------------------------

bool isSafe(const vector<vector<int>>& board, int row, int col, int n) {
    // Check the same row to the left
    for (int j = 0; j < col; j++)
        if (board[row][j]) return false;

    // Check upper-left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return false;

    // Check lower-left diagonal
    for (int i = row, j = col; i < n && j >= 0; i++, j--)
        if (board[i][j]) return false;

    return true;
}

// ---- Print Board -----------------------------------------------------

void printBoard(const vector<vector<int>>& board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << (board[i][j] ? " Q " : " . ");
        cout << endl;
    }
    cout << endl;
}

// ---- Backtracking ----------------------------------------------------

// Place queens one column at a time; return true when first solution found
bool solve(vector<vector<int>>& board, int col, int n) {
    if (col == n) {
        // All n queens placed successfully
        cout << "Solution:" << endl;
        printBoard(board, n);
        return true;
    }

    for (int row = 0; row < n; row++) {
        if (isSafe(board, row, col, n)) {
            board[row][col] = 1;

            if (solve(board, col + 1, n))
                return true;  // stop after the first solution is found

            board[row][col] = 0;  // backtrack: undo placement
        }
    }

    return false;  // no valid row found in this column
}

// ---- Main ------------------------------------------------------------

int main() {
    int n;
    cout << "Enter number of queens (N): ";
    cin >> n;

    vector<vector<int>> board(n, vector<int>(n, 0));

    auto start = chrono::high_resolution_clock::now();

    bool solved = solve(board, 0, n);

    auto stop     = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    if (!solved)
        cout << "No solution exists for N = " << n << "." << endl;

    cout << "Time: " << dur << " microseconds" << endl;

    return 0;
}
