/*
 * Coin Change — Greedy Approach
 *
 * ---------------------------------------------------------------
 * Sort denominations in descending order. At each step, use the
 * largest denomination that still fits into the remaining amount.
 *
 * Time  : O(n log n + amount)  — sort + greedy loop
 * Space : O(n)                 — denomination list
 *
 * NOTE: This greedy approach does NOT always give the optimal
 *       (minimum) number of coins for arbitrary denominations.
 *       It works correctly for standard currency systems
 *       like {1, 5, 10, 25} but may fail for others (e.g., {1,3,4}).
 *       For the guaranteed optimal solution, use DP (practical3_1).
 * ---------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

// ---- Core Algorithm --------------------------------------------------

void coinChangeGreedy(vector<int>& denominations, int amount) {
    // Sort largest denomination first
    sort(denominations.begin(), denominations.end(), greater<int>());

    int coinsUsed = 0;
    int remaining = amount;

    cout << "Coins used: ";
    for (int coin : denominations) {
        // Use this coin as many times as it fits
        while (remaining >= coin) {
            cout << coin << " ";
            remaining -= coin;
            coinsUsed++;
        }
    }
    cout << endl;

    if (remaining == 0)
        cout << "Total coins used : " << coinsUsed << endl;
    else
        cout << "Cannot make exact change. Remainder: " << remaining << endl;
}

// ---- Main ------------------------------------------------------------

int main() {
    int n, amount;

    cout << "Enter number of denominations : ";
    cin >> n;

    vector<int> denominations(n);
    cout << "Enter denominations           : ";
    for (int i = 0; i < n; i++)
        cin >> denominations[i];

    cout << "Enter target amount           : ";
    cin >> amount;

    auto start = chrono::high_resolution_clock::now();

    coinChangeGreedy(denominations, amount);

    auto stop     = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    cout << "Time             : " << dur << " microseconds" << endl;

    return 0;
}
