// Practical 1.4 - Large Integer Multiplication
// Grade-school digit-by-digit multiplication for arbitrarily large integers.
// Time: O(n * m) where n, m are digit counts of the two numbers.

#include <bits/stdc++.h>
using namespace std;

void multiplyBigInt(const string& a, const string& b) {
    int n = a.size(), m = b.size();

    if ((n == 1 && a[0] == '0') || (m == 1 && b[0] == '0')) {
        cout << "Product: 0\n";
        return;
    }

    // Result can have at most n+m digits
    vector<int> result(n + m, 0);

    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            int mul = (a[i] - '0') * (b[j] - '0');
            int p1 = i + j, p2 = i + j + 1;
            int sum = mul + result[p2];
            result[p2] = sum % 10;
            result[p1] += sum / 10;
        }
    }

    cout << "Product: ";
    bool leading = true;
    for (int d : result) {
        if (leading && d == 0) continue;
        leading = false;
        cout << d;
    }
    if (leading) cout << "0";
    cout << "\n";
}

int main() {
    string a, b;
    cout << "Enter first number: ";
    cin >> a;
    cout << "Enter second number: ";
    cin >> b;

    auto start = chrono::high_resolution_clock::now();
    multiplyBigInt(a, b);
    auto end = chrono::high_resolution_clock::now();

    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us\n";
    return 0;
}
