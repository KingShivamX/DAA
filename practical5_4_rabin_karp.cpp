/*
 * Rabin-Karp Pattern Matching (Rolling Hash)
 *
 * ---------------------------------------------------------------
 * Use a rolling hash to compare the pattern against a sliding window
 * of the text in O(1) per step. When hashes match, verify the
 * actual characters to rule out hash collisions (spurious hits).
 *
 * Rolling hash formula:
 *   hash = (BASE * hash + char) % PRIME
 *   Slide window: drop leftmost char, add rightmost char in O(1).
 *
 * Let n = length of text, m = length of pattern.
 *
 * Time  : Average O(n + m)  — few hash collisions expected
 *         Worst   O(n * m)  — all windows produce the same hash
 * Space : O(1)              — only a few integer variables
 * ---------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <chrono>

using namespace std;

const int BASE  = 256;   // number of characters in input alphabet
const int PRIME = 101;   // a prime number used to reduce hash collisions

// ---- Core Algorithm --------------------------------------------------

void rabinKarpSearch(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();

    if (m > n) {
        cout << "Pattern is longer than text." << endl;
        return;
    }

    // h = BASE^(m-1) % PRIME  — used to remove the leading digit
    int h = 1;
    for (int i = 0; i < m - 1; i++)
        h = (h * BASE) % PRIME;

    // Compute hash for pattern and for the first window of text
    int patHash = 0;
    int winHash = 0;
    for (int i = 0; i < m; i++) {
        patHash = (BASE * patHash + pattern[i]) % PRIME;
        winHash = (BASE * winHash + text[i])    % PRIME;
    }

    bool found = false;

    for (int i = 0; i <= n - m; i++) {
        if (patHash == winHash) {
            // Hashes match: verify character by character to confirm
            if (text.substr(i, m) == pattern) {
                cout << "Pattern found at index: " << i << endl;
                found = true;
            }
        }

        // Compute rolling hash for the next window
        if (i < n - m) {
            winHash = (BASE * (winHash - (unsigned char)text[i] * h)
                       + (unsigned char)text[i + m]) % PRIME;

            // Keep hash non-negative
            if (winHash < 0)
                winHash += PRIME;
        }
    }

    if (!found)
        cout << "Pattern not found." << endl;
}

// ---- Main ------------------------------------------------------------

int main() {
    string text, pattern;

    cout << "Enter text    : ";
    getline(cin, text);

    cout << "Enter pattern : ";
    getline(cin, pattern);

    auto start = chrono::high_resolution_clock::now();

    rabinKarpSearch(text, pattern);

    auto stop     = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    cout << "Time: " << dur << " microseconds" << endl;

    return 0;
}
