/*
 * Boyer-Moore Pattern Matching (Bad Character + Good Suffix Heuristics)
 *
 * ---------------------------------------------------------------
 * Preprocesses the pattern with two tables:
 *   Bad Character : on mismatch, shift so the mismatched text char
 *                   aligns with its last occurrence in the pattern.
 *   Good Suffix   : on mismatch, shift so the already-matched suffix
 *                   aligns with its next occurrence in the pattern,
 *                   or a prefix of the pattern that matches a suffix.
 * The larger of the two shifts is always applied.
 *
 * Let n = length of text, m = length of pattern.
 *
 * Time  : Best    O(n / m)  — large skips on rare pattern characters
 *         Average O(n)      — very fast in practice
 *         Worst   O(n * m)  — only bad-character tables; good-suffix
 *                             brings worst-case down to O(n)
 * Space : O(m + 256)        — good suffix table + bad character table
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
vector<int> buildBadCharTable(const string& pat) {
    vector<int> bc(256, -1);
    for (int i = 0; i < (int)pat.size(); i++)
        bc[(unsigned char)pat[i]] = i;
    return bc;
}

// ---- Good Suffix Table -----------------------------------------------

// shift[k] = minimum shift when the last k characters of pattern matched
//   shift[0] = shift after a full match
//   shift[k] = shift when mismatch after matching k chars from the right
//
// Uses the border (failure-function) approach:
//   bpos[i] = start of the next border for pat[i..m]
void buildGoodSuffixTable(const string& pat, vector<int>& shift) {
    int m = pat.size();
    shift.assign(m + 1, 0);
    vector<int> bpos(m + 2, 0);

    // Part 1: for each position, record shift based on strong suffix borders
    int i = m, j = m + 1;
    bpos[i] = j;
    while (i > 0) {
        while (j <= m && pat[i - 1] != pat[j - 1]) {
            if (shift[j] == 0)
                shift[j] = j - i;   // shift so the suffix of length j-i aligns
            j = bpos[j];
        }
        i--;
        j--;
        bpos[i] = j;
    }

    // Part 2: if no occurrence found, use longest prefix that is also a suffix
    j = bpos[0];
    for (i = 0; i <= m; i++) {
        if (shift[i] == 0)
            shift[i] = j;
        if (i == j)
            j = bpos[j];
    }
}

// ---- Core Algorithm --------------------------------------------------

void boyerMooreSearch(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();

    vector<int> badChar  = buildBadCharTable(pattern);
    vector<int> goodSuffix;
    buildGoodSuffixTable(pattern, goodSuffix);

    int  s     = 0;       // current alignment of pattern over text
    bool found = false;

    while (s <= n - m) {
        int j = m - 1;

        // Match from right to left
        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        if (j < 0) {
            // Full match: shift using good suffix rule for complete match
            cout << "Pattern found at index: " << s << endl;
            found = true;
            s += goodSuffix[0];
        } else {
            // Mismatch at j: (m-1-j) chars matched from the right
            int bcShift = j - badChar[(unsigned char)text[s + j]];
            int gsShift = goodSuffix[j + 1]; // good suffix shift for j+1 matched chars
            s += max(bcShift, gsShift);
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
