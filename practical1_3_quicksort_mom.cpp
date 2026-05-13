/*
 * QuickSort with Median of Medians (MoM) Pivot Selection
 *
 * ---------------------------------------------------------------
 * Median of Medians guarantees the pivot splits the array at least
 * 30/70, ensuring the worst-case recursion depth stays O(log n).
 *
 * Time  : O(n log n)   — guaranteed worst case
 *         (Standard QuickSort is O(n^2) in the worst case.)
 * Space : O(log n)     — recursion stack
 *
 * Note: MoM adds a constant overhead, so it is slower in practice
 *       than randomized QuickSort, but theoretically optimal.
 * ---------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

// ---- Median of Medians -----------------------------------------------

// Sort a small group and return its median value
int getMedian(vector<int> group) {
    sort(group.begin(), group.end());
    return group[group.size() / 2];
}

// Recursively find the median-of-medians of an array (passed by value)
int getMoMPivot(vector<int> arr) {
    int n = arr.size();

    // Base case: 5 or fewer elements — just return the median directly
    if (n <= 5)
        return getMedian(arr);

    // Split into groups of 5 and collect each group's median
    vector<int> medians;
    for (int i = 0; i < n; i += 5) {
        int groupSize = min(5, n - i);
        vector<int> group(arr.begin() + i, arr.begin() + i + groupSize);
        medians.push_back(getMedian(group));
    }

    // Recursively find the median of the collected medians
    return getMoMPivot(medians);
}

// ---- Partition & Sort ------------------------------------------------

// Partition arr[low..high] around a specific pivot value
int partition(vector<int>& arr, int low, int high, int pivotValue) {
    // Move the pivot to the end so we can use the standard partition
    for (int i = low; i <= high; i++) {
        if (arr[i] == pivotValue) {
            swap(arr[i], arr[high]);
            break;
        }
    }

    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivotValue) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortMoM(vector<int>& arr, int low, int high) {
    if (low >= high)
        return;

    // Extract the subarray, find its MoM pivot value
    vector<int> sub(arr.begin() + low, arr.begin() + high + 1);
    int pivotValue = getMoMPivot(sub);

    // Partition the original array around this pivot
    int pivotPos = partition(arr, low, high, pivotValue);

    quickSortMoM(arr, low,          pivotPos - 1);
    quickSortMoM(arr, pivotPos + 1, high);
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

    quickSortMoM(arr, 0, n - 1);

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
