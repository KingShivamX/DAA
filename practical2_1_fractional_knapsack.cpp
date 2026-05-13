// Practical 2.1 - Fractional Knapsack (Greedy)
// Sort items by value/weight ratio descending, greedily fill the knapsack.
// Fractions of items allowed. Time: O(n log n)

#include <bits/stdc++.h>
using namespace std;

struct Item {
    int value, weight;
    double ratio;
};

int main() {
    int n, cap;
    cout << "Enter number of items: ";
    cin >> n;
    cout << "Enter capacity: ";
    cin >> cap;

    vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << " value weight: ";
        cin >> items[i].value >> items[i].weight;
        items[i].ratio = (double)items[i].value / items[i].weight;
    }

    // Sort by value/weight ratio descending
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.ratio > b.ratio;
    });

    double total = 0;
    int rem = cap;
    for (auto& item : items) {
        if (rem >= item.weight) {
            total += item.value;
            rem -= item.weight;
        } else {
            total += item.value * ((double)rem / item.weight);
            break;
        }
    }

    cout << "Max value: " << total << "\n";
    return 0;
}
