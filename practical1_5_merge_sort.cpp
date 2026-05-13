// Practical 1.5 - Merge Sort (Divide and Conquer)
// Recursively split array into halves, sort each half, then merge them back.
// Time: O(n log n) | Space: O(n)

#include <bits/stdc++.h>
using namespace std;

void merge(int arr[], int lo, int mid, int hi) {
    int n1 = mid - lo + 1, n2 = hi - mid;
    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[lo + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = lo;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int lo, int hi) {
    if (lo >= hi) return;
    int mid = lo + (hi - lo) / 2;
    mergeSort(arr, lo, mid);
    mergeSort(arr, mid + 1, hi);
    merge(arr, lo, mid, hi);
}

int main() {
    srand(time(0));
    int n;
    cout << "Enter n: ";
    cin >> n;

    int manual;
    cout << "Manual input? (1=yes, 0=random): ";
    cin >> manual;

    int* arr = new int[n];
    if (manual) {
        cout << "Enter elements: ";
        for (int i = 0; i < n; i++) cin >> arr[i];
    } else {
        for (int i = 0; i < n; i++) arr[i] = rand() % 100000;
    }

    if (n <= 20) { cout << "Before: "; for (int i = 0; i < n; i++) cout << arr[i] << " "; cout << "\n"; }

    auto start = chrono::high_resolution_clock::now();
    mergeSort(arr, 0, n - 1);
    auto end = chrono::high_resolution_clock::now();

    if (n <= 20) { cout << "After:  "; for (int i = 0; i < n; i++) cout << arr[i] << " "; cout << "\n"; }
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us\n";

    delete[] arr;
    return 0;
}
