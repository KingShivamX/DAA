// Practical 1.3 - QuickSort with Median of Medians (MoM) Pivot
// Groups elements into sets of 5, finds their medians, picks median of those as pivot.
// Guarantees O(n log n) worst-case by ensuring a balanced partition every time.

#include <bits/stdc++.h>
using namespace std;

// Sort small group and return its median
int median(int arr[], int n) {
    sort(arr, arr + n);
    return arr[n / 2];
}

// Recursively find the median-of-medians pivot value
int getMoMPivot(int arr[], int lo, int hi) {
    int n = hi - lo + 1;
    if (n <= 5) {
        int tmp[5];
        for (int i = 0; i < n; i++) tmp[i] = arr[lo + i];
        return median(tmp, n);
    }

    int groups = (n + 4) / 5;
    int* medians = new int[groups];
    for (int g = 0; g < groups; g++) {
        int start = lo + g * 5;
        int size  = (g == groups - 1 && n % 5 != 0) ? n % 5 : 5;
        int tmp[5];
        for (int i = 0; i < size; i++) tmp[i] = arr[start + i];
        medians[g] = median(tmp, size);
    }

    int result = getMoMPivot(medians, 0, groups - 1);
    delete[] medians;
    return result;
}

// Partition array around a given pivot value
int partition(int arr[], int lo, int hi, int pivotVal) {
    // Move pivot to end
    for (int i = lo; i <= hi; i++)
        if (arr[i] == pivotVal) { swap(arr[i], arr[hi]); break; }

    int i = lo - 1;
    for (int j = lo; j < hi; j++)
        if (arr[j] <= pivotVal) swap(arr[++i], arr[j]);

    swap(arr[i + 1], arr[hi]);
    return i + 1;
}

void quickSortMoM(int arr[], int lo, int hi) {
    if (lo < hi) {
        int pivot = getMoMPivot(arr, lo, hi);
        int p = partition(arr, lo, hi, pivot);
        quickSortMoM(arr, lo, p - 1);
        quickSortMoM(arr, p + 1, hi);
    }
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
    quickSortMoM(arr, 0, n - 1);
    auto end = chrono::high_resolution_clock::now();

    if (n <= 20) { cout << "After:  "; for (int i = 0; i < n; i++) cout << arr[i] << " "; cout << "\n"; }
    cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us\n";

    delete[] arr;
    return 0;
}
