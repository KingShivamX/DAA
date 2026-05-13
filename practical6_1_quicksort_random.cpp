/*
 * Randomized QuickSort
 *
 * ---------------------------------------------------------------
 * Standard QuickSort with a randomly chosen pivot instead of
 * always picking the last element. This eliminates worst-case
 * behaviour on already-sorted or reverse-sorted inputs.
 *
 * Time  : Best    O(n log n)  — perfectly balanced splits
 *         Average O(n log n)  — expected with random pivot
 *         Worst   O(n^2)      — extremely unlikely with random pivot
 * Space : O(log n)            — recursion stack
 * ---------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

// ---- Partition -------------------------------------------------------

// Standard Lomuto partition around arr[high]
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i     = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Randomly pick a pivot and swap it to the end before partitioning
int randomizedPartition(vector<int>& arr, int low, int high) {
    int randomIdx = low + rand() % (high - low + 1);
    swap(arr[randomIdx], arr[high]);
    return partition(arr, low, high);
}

// ---- Sort ------------------------------------------------------------

void randomizedQuickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIdx = randomizedPartition(arr, low, high);
        randomizedQuickSort(arr, low,          pivotIdx - 1);
        randomizedQuickSort(arr, pivotIdx + 1, high);
    }
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

    randomizedQuickSort(arr, 0, n - 1);

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
