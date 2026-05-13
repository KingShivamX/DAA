/*
 * Fractional Knapsack (Greedy Algorithm)
 *
 * ---------------------------------------------------------------
 * Sort items by value/weight ratio (descending). Greedily pick
 * items with the highest ratio. Fractions of an item are allowed.
 *
 * Time  : O(n log n)  — dominated by sorting
 * Space : O(n)        — item list
 * ---------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

struct Item {
    int    value;
    int    weight;
    double ratio;   // value per unit weight
};

// ---- Core Algorithm --------------------------------------------------

double fractionalKnapsack(int capacity, vector<Item>& items) {
    // Sort items by ratio in descending order
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.ratio > b.ratio;
    });

    double totalValue = 0.0;
    int    remaining  = capacity;

    for (const Item& item : items) {
        if (remaining <= 0)
            break;

        if (item.weight <= remaining) {
            // Take the whole item
            totalValue += item.value;
            remaining  -= item.weight;
        } else {
            // Take only the fraction that fits
            double fraction = (double)remaining / item.weight;
            totalValue += item.value * fraction;
            remaining   = 0;
        }
    }

    return totalValue;
}

// ---- Main ------------------------------------------------------------

int main() {
    int n, capacity;

    cout << "Enter number of items   : ";
    cin >> n;
    cout << "Enter knapsack capacity : ";
    cin >> capacity;

    vector<Item> items(n);
    cout << "Enter value and weight for each item:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  Item " << i + 1 << " (value weight): ";
        cin >> items[i].value >> items[i].weight;
        items[i].ratio = (double)items[i].value / items[i].weight;
    }

    auto start = chrono::high_resolution_clock::now();

    double maxValue = fractionalKnapsack(capacity, items);

    auto stop     = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    cout << "\nMaximum value : " << maxValue << endl;
    cout << "Time          : " << dur << " microseconds" << endl;

    return 0;
}
