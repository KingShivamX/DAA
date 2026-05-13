// Practical 5.4 - Rabin-Karp Pattern Matching (Rolling Hash)
// Compute hash of pattern and each text window; verify on hash match to handle collisions.
// Time: O(n + m) average, O(nm) worst case (due to collisions)

#include <bits/stdc++.h>
using namespace std;

void rabinKarp(const string& text, const string& pat, int prime = 101) {
    int n = text.size(), m = pat.size();
    const int d = 256; // number of characters in alphabet

    // h = d^(m-1) % prime, used to remove leading digit from rolling hash
    int h = 1;
    for (int i = 0; i < m - 1; i++) h = (h * d) % prime;

    int ph = 0, wh = 0;
    for (int i = 0; i < m; i++) {
        ph = (d * ph + pat[i])  % prime;
        wh = (d * wh + text[i]) % prime;
    }

    bool found = false;
    for (int i = 0; i <= n - m; i++) {
        if (ph == wh) {
            // Hash matched; verify character by character to rule out collision
            if (text.substr(i, m) == pat) {
                cout << "Pattern found at index: " << i << "\n";
                found = true;
            }
        }
        // Slide window: remove leading char, add next char
        if (i < n - m) {
            wh = (d * (wh - text[i] * h) + text[i + m]) % prime;
            if (wh < 0) wh += prime;
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

    rabinKarp(text, pat);
    return 0;
}
