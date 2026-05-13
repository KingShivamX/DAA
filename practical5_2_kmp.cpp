// Practical 5.2 - KMP (Knuth-Morris-Pratt) Pattern Matching
// Precompute LPS (longest proper prefix which is also suffix) table to skip redundant comparisons.
// Time: O(n + m) | Preprocessing: O(m)

#include <bits/stdc++.h>
using namespace std;

// Build LPS table: lps[i] = length of longest proper prefix of pat[0..i] that is also a suffix
vector<int> buildLPS(const string& pat) {
    int m = pat.size();
    vector<int> lps(m, 0);
    int len = 0, i = 1;

    while (i < m) {
        if (pat[i] == pat[len]) {
            lps[i++] = ++len;
        } else if (len) {
            len = lps[len - 1]; // fallback without moving i
        } else {
            lps[i++] = 0;
        }
    }
    return lps;
}

void kmpSearch(const string& text, const string& pat) {
    int m = pat.size();
    auto lps = buildLPS(pat);

    cout << "LPS table: ";
    for (int x : lps) cout << x << " ";
    cout << "\n";

    int n = text.size(), i = 0, j = 0;
    bool found = false;

    while (i < n) {
        if (text[i] == pat[j]) {
            i++; j++;
            if (j == m) {
                cout << "Pattern found at index: " << i - m << "\n";
                found = true;
                j = lps[m - 1]; // prepare for overlapping match
            }
        } else {
            // Mismatch: use LPS to skip re-comparisons
            if (j != 0) j = lps[j - 1];
            else        i++;
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

    kmpSearch(text, pat);
    return 0;
}
