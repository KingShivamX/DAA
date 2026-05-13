/*
 * Boyer-Moore Pattern Matching (Bad Character Heuristic)
 *
 * ---------------------------------------------------------------
 * Preprocess the pattern to record the rightmost position of each
 * character. Search right-to-left within each alignment window.
 * On a mismatch, use the bad character table to compute a large skip.
 *
 * Let n = length of text, m = length of pattern.
 *
 * Time  : Best    O(n / m)  — large skips when pattern chars are rare
 *         Average O(n)      — very fast in practice
 *         Worst   O(n * m)  — e.g., text = "AAAA", pattern = "AAA"
 * Space : O(256)            — bad character table (all ASCII chars)
 * ---------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

// ---- Bad Character Table ---------------------------------------------

// badChar[c] = rightmost index of character c in the pattern, or -1
vector<int> buildBadCharTable(const string& pattern) {
    vector<int> badChar(256, -1);
    for (int i = 0; i < (int)pattern.size(); i++)
        badChar[(unsigned char)pattern[i]] = i;
    return badChar;
}

// ---- Core Algorithm --------------------------------------------------

void boyerMooreSearch(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();

    vector<int> badChar = buildBadCharTable(pattern);

    int  shift = 0;   // current alignment of pattern over text
    bool found = false;

    while (shift <= n - m) {
        int j = m - 1;

        // Match from right to left
        while (j >= 0 && pattern[j] == text[shift + j])
            j--;

        if (j < 0) {
            // Full match found at 'shift'
            cout << "Pattern found at index: " << shift << endl;
            found = true;

            // Shift so the next character in text aligns with
            // its last known position in the pattern
            int nextAlign = (shift + m < n)
                          ? m - badChar[(unsigned char)text[shift + m]]
                          : 1;
            shift += nextAlign;
        } else {
            // Bad character: shift pattern so the mismatched text character
            // aligns with its rightmost occurrence in the pattern
            int skip = j - badChar[(unsigned char)text[shift + j]];
            shift += max(1, skip);
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

    boyerMooreSearch(text, pattern);

    auto stop     = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    cout << "Time: " << dur << " microseconds" << endl;

    return 0;
}
