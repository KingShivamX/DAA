/*
 * Travelling Salesman Problem — Bitmask Dynamic Programming
 *
 * ---------------------------------------------------------------
 * Find the minimum-cost Hamiltonian cycle through all n cities,
 * starting and ending at city 0.
 *
 * State: dp[mask][i] = minimum cost to visit exactly the cities
 *        in 'mask' and currently be at city i (starting from 0).
 *
 * Transition:
 *   For each unvisited city j:
 *     dp[mask|(1<<j)][j] = min(dp[mask][i] + dist[i][j])
 *
 * Base case : dp[1][0] = 0  (only city 0 visited, cost 0)
 * Answer    : min over all i of (dp[(1<<n)-1][i] + dist[i][0])
 *
 * Time  : O(n^2 * 2^n)  — n cities, 2^n masks, n transitions each
 * Space : O(n * 2^n)    — dp and parent tables
 *
 * Practical limit: n <= 20 (larger n needs too much memory/time).
 * ---------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

const int INF = 1e9;

int n;
vector<vector<int>> dist;
vector<vector<int>> dp;
vector<vector<int>> parent;  // to reconstruct the path

// ---- Core Algorithm --------------------------------------------------

int tsp(int mask, int pos) {
    // All cities visited: return cost to close the cycle back to city 0
    if (mask == (1 << n) - 1)
        return dist[pos][0];

    // Return cached result if already computed
    if (dp[mask][pos] != -1)
        return dp[mask][pos];

    int best     = INF;
    int bestNext = -1;

    // Try each city that has not been visited yet
    for (int city = 0; city < n; city++) {
        if (mask & (1 << city))
            continue;  // already visited

        int newMask = mask | (1 << city);
        int cost    = dist[pos][city] + tsp(newMask, city);

        if (cost < best) {
            best     = cost;
            bestNext = city;
        }
    }

    dp[mask][pos]     = best;
    parent[mask][pos] = bestNext;
    return best;
}

// ---- Main ------------------------------------------------------------

int main() {
    cout << "Enter number of cities: ";
    cin >> n;

    dist.assign(n, vector<int>(n));
    cout << "Enter the " << n << "x" << n << " distance matrix:" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> dist[i][j];

    int states = 1 << n;
    dp.assign(states,     vector<int>(n, -1));
    parent.assign(states, vector<int>(n, -1));

    auto start = chrono::high_resolution_clock::now();

    // Start from city 0 with only city 0 marked as visited (mask = 1)
    int minCost = tsp(1, 0);

    auto stop     = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    cout << "\nMinimum tour cost : " << minCost << endl;

    // Reconstruct and print the optimal path
    cout << "Optimal path      : 0";
    int mask = 1, pos = 0;
    while (parent[mask][pos] != -1) {
        int next = parent[mask][pos];
        cout << " -> " << next;
        mask |= (1 << next);
        pos   = next;
    }
    cout << " -> 0" << endl;

    cout << "Time              : " << dur << " microseconds" << endl;

    return 0;
}
