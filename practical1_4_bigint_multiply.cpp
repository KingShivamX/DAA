/*
 * Large Integer Multiplication (Grade-School Method)
 *
 * ---------------------------------------------------------------
 * Multiplies two arbitrarily large integers represented as strings.
 * Uses the standard grade-school digit-by-digit multiplication.
 *
 * Let m = digits in the first number, n = digits in the second.
 *
 * Time  : O(m * n)   — each digit of the first multiplied by each
 *                      digit of the second
 * Space : O(m + n)   — result has at most m + n digits
 * ---------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

// ---- Core Algorithm --------------------------------------------------

string multiplyLargeIntegers(const string& a, const string& b) {
    int m = a.size();
    int n = b.size();

    // The product has at most m + n digits
    vector<int> result(m + n, 0);

    // Multiply every digit of 'a' with every digit of 'b'
    // and accumulate in the correct position
    for (int i = m - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            int mul  = (a[i] - '0') * (b[j] - '0');
            int pos1 = i + j;      // carry goes here
            int pos2 = i + j + 1;  // current digit goes here

            int total = mul + result[pos2];

            result[pos2] = total % 10;
            result[pos1] += total / 10;
        }
    }

    // Build the result string, skip any leading zeros
    string product = "";
    for (int digit : result) {
        if (!(product.empty() && digit == 0))
            product += to_string(digit);
    }

    return product.empty() ? "0" : product;
}

// ---- Main ------------------------------------------------------------

int main() {
    string a, b;

    cout << "Enter first large integer  : ";
    cin >> a;
    cout << "Enter second large integer : ";
    cin >> b;

    auto start = chrono::high_resolution_clock::now();

    string product = multiplyLargeIntegers(a, b);

    auto stop     = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    cout << "\nProduct : " << product << endl;
    cout << "Time    : " << dur << " microseconds" << endl;

    return 0;
}
