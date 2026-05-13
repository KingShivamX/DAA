/*
 * Naive (Brute-Force) Pattern Matching
 *
 * ---------------------------------------------------------------
 * Slide the pattern over the text one character at a time and
 * check for a match at each position.
 *
 * Let n = length of text, m = length of pattern.
 *
 * Time  : Best  O(n)    — first character of pattern never matches
 *         Worst O(n*m)  — e.g., text = "AAAA...A", pattern = "AAAB"
 * Space : O(1)          — no extra data structures needed
 * ---------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <chrono>

using namespace std;

// ---- Core Algorithm --------------------------------------------------

void naiveSearch(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();
    bool found = false;

    for (int i = 0; i <= n - m; i++) {
        // Compare pattern against text starting at position i
        int j = 0;
        while (j < m && text[i + j] == pattern[j])
            j++;

        if (j == m) {
            cout << "Pattern found at index: " << i << endl;
            found = true;
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

    naiveSearch(text, pattern);

    auto stop     = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    cout << "Time: " << dur << " microseconds" << endl;

    return 0;
}
