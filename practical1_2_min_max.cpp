/*
 * Min and Max using Divide and Conquer
 *
 * ---------------------------------------------------------------
 * Algorithm:
 *   Recursively split the array in half. Find the min and max of
 *   each half, then combine by comparing the two halves.
 *
 * Time  : O(n)       — every element is visited exactly once
 * Space : O(log n)   — recursion stack depth
 *
 * Comparison count: ~3n/2 - 2
 *   Better than the naive 2(n-1) comparisons approach.
 * ---------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

struct MinMax {
    int min;
    int max;
};

// ---- Core Algorithm --------------------------------------------------

MinMax findMinMax(const vector<int>& arr, int low, int high) {
    // Base case: only one element
    if (low == high)
        return {arr[low], arr[low]};

    // Base case: two elements — direct comparison
    if (high == low + 1) {
        if (arr[low] < arr[high])
            return {arr[low], arr[high]};
        else
            return {arr[high], arr[low]};
    }

    // Divide into left and right halves
    int mid = (low + high) / 2;

    MinMax left  = findMinMax(arr, low, mid);
    MinMax right = findMinMax(arr, mid + 1, high);

    // Combine: take the best from each half
    MinMax result;
    result.min = (left.min < right.min) ? left.min : right.min;
    result.max = (left.max > right.max) ? left.max : right.max;

    return result;
}

// ---- Main ------------------------------------------------------------

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    auto start = chrono::high_resolution_clock::now();

    MinMax result = findMinMax(arr, 0, n - 1);

    auto stop     = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    cout << "\nMinimum : " << result.min << endl;
    cout << "Maximum : " << result.max << endl;
    cout << "Time    : " << dur << " microseconds" << endl;

    return 0;
}
