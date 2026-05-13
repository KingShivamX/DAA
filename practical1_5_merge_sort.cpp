/*
 * Merge Sort (Divide and Conquer)
 *
 * ---------------------------------------------------------------
 * Recursively divide the array into two halves, sort each half,
 * then merge the two sorted halves back together.
 *
 * Time  : O(n log n)  — Best / Average / Worst (always the same)
 * Space : O(n)        — temporary arrays used during the merge step
 * ---------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

// ---- Merge -----------------------------------------------------------

// Merge the two sorted halves arr[low..mid] and arr[mid+1..high]
void merge(vector<int>& arr, int low, int mid, int high) {
    // Copy both halves into temporary vectors
    vector<int> left(arr.begin() + low,     arr.begin() + mid + 1);
    vector<int> right(arr.begin() + mid + 1, arr.begin() + high + 1);

    int i = 0, j = 0, k = low;

    // Merge back in sorted order by comparing front elements
    while (i < (int)left.size() && j < (int)right.size()) {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    // Copy any leftover elements from either half
    while (i < (int)left.size())  arr[k++] = left[i++];
    while (j < (int)right.size()) arr[k++] = right[j++];
}

// ---- Sort ------------------------------------------------------------

void mergeSort(vector<int>& arr, int low, int high) {
    if (low >= high)
        return;

    int mid = low + (high - low) / 2;

    mergeSort(arr, low,     mid);
    mergeSort(arr, mid + 1, high);

    merge(arr, low, mid, high);
}

// ---- Helpers ---------------------------------------------------------

void printArray(const vector<int>& arr) {
    for (int x : arr)
        cout << x << " ";
    cout << endl;
}

// ---- Main ------------------------------------------------------------

int main() {
    srand(time(0));

    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    int choice;
    cout << "Press 1 for manual input, 0 for random: ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter " << n << " elements: ";
        for (int i = 0; i < n; i++)
            cin >> arr[i];
    } else {
        for (int i = 0; i < n; i++)
            arr[i] = rand() % 100000;
    }

    if (n <= 50) {
        cout << "Original : ";
        printArray(arr);
    }

    auto start = chrono::high_resolution_clock::now();

    mergeSort(arr, 0, n - 1);

    auto stop     = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    if (n <= 50) {
        cout << "Sorted   : ";
        printArray(arr);
    } else {
        cout << n << " elements sorted successfully." << endl;
    }

    cout << "Time     : " << dur << " microseconds" << endl;

    return 0;
}
