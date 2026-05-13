/*
 * Large Integer Multiplication - Karatsuba Algorithm (Divide and Conquer)
 *
 * ---------------------------------------------------------------
 * Splits each n-digit number into two halves (high and low), then
 * uses only 3 recursive multiplications instead of 4:
 *
 *   x = xh * 10^m + xl          (split x at the midpoint m)
 *   y = yh * 10^m + yl
 *
 *   z0 = xl * yl
 *   z2 = xh * yh
 *   z1 = (xl + xh) * (yl + yh) - z0 - z2     <-- only 1 multiply
 *
 *   result = z2 * 10^(2m)  +  z1 * 10^m  +  z0
 *
 * Let n = number of digits in the larger number.
 *
 * Time  : O(n^1.585)  — Karatsuba (3 recursive calls, exponent = log2(3))
 *         O(n^2)      — grade-school (for comparison)
 * Space : O(n log n)  — recursive call stack depth is O(log n)
 * ---------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <chrono>
#include <cmath>
#include <algorithm>

using namespace std;

// ---- Helper: integer power of 10 (avoids floating-point inaccuracy) ---

long long pow10(int n) {
    long long result = 1;
    for (int i = 0; i < n; i++)
        result *= 10;
    return result;
}

// ---- Karatsuba Algorithm ---------------------------------------------

// Works correctly for non-negative long long values.
// For numbers larger than ~10^9, the intermediate sums can overflow
// long long; for a true arbitrary-precision version use string/vector.
long long karatsuba(long long x, long long y) {
    // Base case: single-digit (or zero) multiplication
    if (x < 10 || y < 10)
        return x * y;

    // Number of digits in the larger operand
    int n = max(to_string(x).size(), to_string(y).size());
    int m = n / 2;            // split point
    long long base = pow10(m);

    // Split each number into high and low halves
    long long xh = x / base,  xl = x % base;
    long long yh = y / base,  yl = y % base;

    // 3 recursive multiplications (instead of the naive 4)
    long long z0 = karatsuba(xl, yl);                       // low  * low
    long long z2 = karatsuba(xh, yh);                       // high * high
    long long z1 = karatsuba(xl + xh, yl + yh) - z0 - z2;  // cross term

    // Combine: z2 * 10^(2m)  +  z1 * 10^m  +  z0
    return z2 * base * base + z1 * base + z0;
}

// ---- Main ------------------------------------------------------------

int main() {
    long long a, b;

    cout << "Enter first number  : ";
    cin >> a;
    cout << "Enter second number : ";
    cin >> b;

    auto start = chrono::high_resolution_clock::now();

    long long product = karatsuba(a, b);

    auto stop     = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    cout << "\nProduct : " << product << endl;
    cout << "Time    : " << dur << " microseconds" << endl;

    return 0;
}
