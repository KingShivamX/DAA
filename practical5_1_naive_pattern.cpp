// Practical 5.1 - Naive Pattern Matching
// Slide the pattern over the text one position at a time, check each window.
// Time: O((n - m + 1) * m) | Simple but no preprocessing.

#include <bits/stdc++.h>
using namespace std;

void naiveSearch(const string& text, const string& pat) {
    int n = text.size(), m = pat.size();
    bool found = false;

    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++)
            if (text[i + j] != pat[j]) break;

        if (j == m) {
            cout << "Pattern found at index: " << i << "\n";
            found = true;
        }
    }

    if (!found) cout << "Pattern not found.\n";
}

int main() {
    string text, pat;
    cout << "Enter text: ";
    getline(cin, text);
    cout << "Enter pattern: ";
    getline(cin, pat);

    naiveSearch(text, pat);
    return 0;
}
