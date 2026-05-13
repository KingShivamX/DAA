// Practical 6.1 - Randomized QuickSort
// Randomly pick a pivot to avoid worst-case O(n^2) on sorted/reverse-sorted input.
// Expected Time: O(n log n) | Space: O(log n) stack

#include <bits/stdc++.h>
using namespace std;

int partition(int arr[], int lo, int hi) {
    int pivot = arr[hi], i = lo - 1;
    for (int j = lo; j < hi; j++)
        if (arr[j] <= pivot) swap(arr[++i], arr[j]);
    swap(arr[i + 1], arr[hi]);
    return i + 1;
}

int randomPartition(int arr[], int lo, int hi) {
    // Swap a random element to the end, then partition around it
    int r = lo + rand() % (hi - lo + 1);
    swap(arr[r], arr[hi]);
    return partition(arr, lo, hi);
}

void quickSort(int arr[], int lo, int hi) {
    if (lo < hi) {
        int p = randomPartition(arr, lo, hi);
        quickSort(arr, lo, p - 1);
        quickSort(arr, p + 1, hi);
    }
}

int main() {
    srand(time(0));
    int n;
    cout << "Enter n: ";
    cin >> n;

    int* arr = new int[n];
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) cin >> arr[i];

    if (n <= 20) { cout << "Before: "; for (int i = 0; i < n; i++) cout << arr[i] << " "; cout << "\n"; }

    auto start = chrono::high_resolution_clock::now();
    quickSort(arr, 0, n - 1);
    auto end = chrono::high_resolution_clock::now();

    if (n <= 20) { cout << "After:  "; for (int i = 0; i < n; i++) cout << arr[i] << " "; cout << "\n"; }
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us\n";

    delete[] arr;
    return 0;
}
