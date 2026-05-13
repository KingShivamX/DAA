// Practical 2.2 - Coin Change (Greedy)
// Sort denominations descending, greedily use the largest coin that fits.
// Note: Only optimal for canonical systems (e.g. standard currency). Time: O(n log n)

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, amount;
    cout << "Enter number of denominations: ";
    cin >> n;

    vector<int> coins(n);
    cout << "Enter denominations: ";
    for (int i = 0; i < n; i++) cin >> coins[i];

    cout << "Enter amount: ";
    cin >> amount;

    sort(coins.rbegin(), coins.rend()); // largest first

    int count = 0;
    cout << "Coins used: ";
    for (int c : coins) {
        while (amount >= c) {
            cout << c << " ";
            amount -= c;
            count++;
        }
    }

    if (amount == 0)
        cout << "\nTotal coins: " << count << "\n";
    else
        cout << "\nCannot make exact change.\n";

    return 0;
}
