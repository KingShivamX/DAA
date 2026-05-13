/*
 * Comparison of Search Algorithms:
 *   Linear Search, Binary Search, Randomized Binary Search
 *
 * ---------------------------------------------------------------
 * Linear Search
 *   Time  : Best O(1) | Average O(n) | Worst O(n)
 *   Space : O(1)
 *
 * Binary Search  (requires sorted array, recursive)
 *   Time  : Best O(1) | Average O(log n) | Worst O(log n)
 *   Space : O(log n)  — recursion stack
 *
 * Randomized Binary Search  (random pivot instead of mid)
 *   Time  : Best O(1) | Average O(log n) | Worst O(n)
 *   Space : O(log n)  — recursion stack
 *
 * Note: All three are benchmarked over 1000 iterations each on a
 *       sorted array, with the last element as the worst-case target.
 * ---------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

// ---- Search Functions ------------------------------------------------

int linearSearch(const vector<int>& arr, int target) {
    for (int i = 0; i < (int)arr.size(); i++) {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

int binarySearch(const vector<int>& arr, int low, int high, int target) {
    if (low > high)
        return -1;

    int mid = low + (high - low) / 2;

    if (arr[mid] == target)  return mid;
    if (arr[mid] > target)   return binarySearch(arr, low, mid - 1, target);
    return binarySearch(arr, mid + 1, high, target);
}

int randomizedBinarySearch(const vector<int>& arr, int low, int high, int target) {
    if (low > high)
        return -1;

    // Pick a random index in [low, high] instead of always using mid
    int pivot = low + rand() % (high - low + 1);

    if (arr[pivot] == target)  return pivot;
    if (arr[pivot] > target)   return randomizedBinarySearch(arr, low, pivot - 1, target);
    return randomizedBinarySearch(arr, pivot + 1, high, target);
}

// ---- Benchmark -------------------------------------------------------

void benchmark(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = i;          // sorted: 0, 1, 2, ..., n-1

    int target     = n - 1;  // worst-case for linear search
    const int REPS = 1000;

    // --- Linear Search ---
    auto t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < REPS; i++)
        linearSearch(arr, target);
    auto t2 = chrono::high_resolution_clock::now();
    long long timeLS = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();

    // --- Binary Search ---
    t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < REPS; i++)
        binarySearch(arr, 0, n - 1, target);
    t2 = chrono::high_resolution_clock::now();
    long long timeBS = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();

    // --- Randomized Binary Search ---
    t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < REPS; i++)
        randomizedBinarySearch(arr, 0, n - 1, target);
    t2 = chrono::high_resolution_clock::now();
    long long timeRBS = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();

    cout << n << "\t\t" << timeLS << "\t\t" << timeBS << "\t\t" << timeRBS << endl;
}

// ---- Main ------------------------------------------------------------

int main() {
    srand(time(0));

    cout << "Benchmarking 1000 iterations per algorithm (time in microseconds)" << endl;
    cout << "Array Size\tLinear\t\tBinary\t\tRand Binary" << endl;
    cout << "------------------------------------------------------------" << endl;

    int sizes[] = {1000, 5000, 10000, 50000};
    for (int s : sizes)
        benchmark(s);

    return 0;
}
