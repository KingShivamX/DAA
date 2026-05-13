/*
 * Knuth-Morris-Pratt (KMP) Pattern Matching
 *
 * ---------------------------------------------------------------
 * Preprocess the pattern to build an LPS (Longest Proper Prefix
 * that is also a Suffix) table. During search, when a mismatch
 * occurs, use the LPS table to skip redundant comparisons instead
 * of restarting from scratch.
 *
 * Let n = length of text, m = length of pattern.
 *
 * Time  : O(n + m)  — O(m) to build LPS, O(n) to search
 * Space : O(m)      — LPS array
 * ---------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

// ---- LPS Table (Failure Function) ------------------------------------

// lps[i] = length of the longest proper prefix of pattern[0..i]
//          that is also a suffix of pattern[0..i]
vector<int> buildLPS(const string& pattern) {
    int m = pattern.size();
    vector<int> lps(m, 0);

    int len = 0;  // length of the previous longest prefix-suffix
    int i   = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            // Characters match: extend the current prefix-suffix
            lps[i++] = ++len;
        } else if (len > 0) {
            // Mismatch after some matches: fall back using LPS
            // (do NOT increment i — we may still match from here)
            len = lps[len - 1];
        } else {
            // No prefix-suffix at all at this position
            lps[i++] = 0;
        }
    }

    return lps;
}

// ---- Core Algorithm --------------------------------------------------

void kmpSearch(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();

    vector<int> lps = buildLPS(pattern);

    cout << "LPS table : ";
    for (int v : lps) cout << v << " ";
    cout << endl;

    int i = 0;  // index into text
    int j = 0;  // index into pattern
    bool found = false;

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }

        if (j == m) {
            // Full match found
            cout << "Pattern found at index: " << i - j << endl;
            found = true;
            j = lps[j - 1];  // use LPS to continue searching
        } else if (i < n && text[i] != pattern[j]) {
            if (j > 0)
                j = lps[j - 1];  // skip using LPS
            else
                i++;
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

    kmpSearch(text, pattern);

    auto stop     = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    cout << "Time: " << dur << " microseconds" << endl;

    return 0;
}
