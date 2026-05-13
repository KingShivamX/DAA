// Practical 5.3 - Boyer-Moore Pattern Matching (Bad Character Heuristic)
// Match pattern right-to-left; on mismatch, shift using bad character table.
// Time: O(n/m) best case, O(nm) worst case | Preprocessing: O(m + 256)

#include <bits/stdc++.h>
using namespace std;

void boyerMoore(const string& text, const string& pat) {
    int n = text.size(), m = pat.size();

    // bad[c] = last index of character c in pattern (-1 if absent)
    int bad[256];
    fill(bad, bad + 256, -1);
    for (int i = 0; i < m; i++) bad[(unsigned char)pat[i]] = i;

    bool found = false;
    int shift = 0;

    while (shift <= n - m) {
        int j = m - 1;

        // Match right to left
        while (j >= 0 && pat[j] == text[shift + j]) j--;

        if (j < 0) {
            cout << "Pattern found at index: " << shift << "\n";
            found = true;
            // Shift so next character aligns with its last occurrence in pattern
            shift += (shift + m < n) ? m - bad[(unsigned char)text[shift + m]] : 1;
        } else {
            // Shift pattern so the mismatched text character aligns with its last occurrence
            shift += max(1, j - bad[(unsigned char)text[shift + j]]);
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

    boyerMoore(text, pat);
    return 0;
}
