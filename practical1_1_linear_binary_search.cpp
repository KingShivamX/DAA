// Practical 1.1 - Linear Search, Binary Search, Randomized Binary Search
// Compares time of three search algorithms across input sizes. Worst-case target used.
// Linear: O(n) | Binary: O(log n) | Randomized Binary: O(log n) expected

#include <bits/stdc++.h>
using namespace std;

int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++)
        if (arr[i] == target) return i;
    return -1;
}

int binarySearch(int arr[], int lo, int hi, int target) {
    if (lo > hi) return -1;
    int mid = lo + (hi - lo) / 2;
    if (arr[mid] == target) return mid;
    if (arr[mid] > target) return binarySearch(arr, lo, mid - 1, target);
    return binarySearch(arr, mid + 1, hi, target);
}

int randomBinarySearch(int arr[], int lo, int hi, int target) {
    if (lo > hi) return -1;
    int pivot = lo + rand() % (hi - lo + 1);
    if (arr[pivot] == target) return pivot;
    if (arr[pivot] > target) return randomBinarySearch(arr, lo, pivot - 1, target);
    return randomBinarySearch(arr, pivot + 1, hi, target);
}

void analyse(int n) {
    int* arr = new int[n];
    for (int i = 0; i < n; i++) arr[i] = i;
    int target = n - 1; // worst case: last element
    const int iter = 1000;
    clock_t s, e;

    s = clock();
    for (int i = 0; i < iter; i++) linearSearch(arr, n, target);
    e = clock();
    double ls = (double)(e - s) / CLOCKS_PER_SEC;

    s = clock();
    for (int i = 0; i < iter; i++) binarySearch(arr, 0, n - 1, target);
    e = clock();
    double bs = (double)(e - s) / CLOCKS_PER_SEC;

    s = clock();
    for (int i = 0; i < iter; i++) randomBinarySearch(arr, 0, n - 1, target);
    e = clock();
    double rbs = (double)(e - s) / CLOCKS_PER_SEC;

    cout << "n=" << n << "  Linear: " << ls << "s  Binary: " << bs << "s  Random: " << rbs << "s\n";
    delete[] arr;
}

int main() {
    srand(time(0));
    int sizes[] = {1000, 5000, 10000, 50000};
    for (int s : sizes) analyse(s);
    return 0;
}
