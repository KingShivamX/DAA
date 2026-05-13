// Practical 1.2 - Min and Max using Divide and Conquer
// Recursively split array into halves, find min/max in each half, merge results.
// Time: O(n) | Comparisons: 3n/2 - 2 (better than 2n-2 linear)

#include <bits/stdc++.h>
using namespace std;

struct Pair { int min, max; };

Pair getMinMax(int arr[], int lo, int hi) {
    if (lo == hi) return {arr[lo], arr[lo]};

    if (hi == lo + 1) {
        if (arr[lo] > arr[hi]) return {arr[hi], arr[lo]};
        return {arr[lo], arr[hi]};
    }

    int mid = (lo + hi) / 2;
    Pair left  = getMinMax(arr, lo, mid);
    Pair right = getMinMax(arr, mid + 1, hi);

    return {min(left.min, right.min), max(left.max, right.max)};
}

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    int* arr = new int[n];
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) cin >> arr[i];

    Pair res = getMinMax(arr, 0, n - 1);
    cout << "Min: " << res.min << "\nMax: " << res.max << "\n";

    delete[] arr;
    return 0;
}
