// Practical 4.1 - N-Queens Problem (Backtracking)
// Place N queens on an N×N board so no two queens share a row, column, or diagonal.
// Try each row in current column; backtrack if no safe position found.

#include <bits/stdc++.h>
using namespace std;

bool isSafe(int** board, int row, int col, int n) {
    // Check same row to the left
    for (int i = 0; i < col; i++)
        if (board[row][i]) return false;

    // Check upper-left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return false;

    // Check lower-left diagonal
    for (int i = row, j = col; i < n && j >= 0; i++, j--)
        if (board[i][j]) return false;

    return true;
}

bool solve(int** board, int col, int n) {
    if (col >= n) return true;

    for (int i = 0; i < n; i++) {
        if (isSafe(board, i, col, n)) {
            board[i][col] = 1;
            if (solve(board, col + 1, n)) return true;
            board[i][col] = 0; // backtrack
        }
    }
    return false;
}

void printBoard(int** board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << (board[i][j] ? " Q" : " .");
        cout << "\n";
    }
}

int main() {
    int n;
    cout << "Enter number of queens: ";
    cin >> n;

    int** board = new int*[n];
    for (int i = 0; i < n; i++) {
        board[i] = new int[n];
        for (int j = 0; j < n; j++) board[i][j] = 0;
    }

    if (solve(board, 0, n))
        printBoard(board, n);
    else
        cout << "No solution exists.\n";

    for (int i = 0; i < n; i++) delete[] board[i];
    delete[] board;
    return 0;
}
