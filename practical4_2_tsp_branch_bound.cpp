/*
 * Travelling Salesman Problem — Branch and Bound
 *
 * ---------------------------------------------------------------
 * Explore the tree of all routes but prune branches where the
 * lower-bound cost already meets or exceeds the best solution found.
 *
 * Lower bound used:
 *   Sum over all cities of (min1_edge + min2_edge) / 2
 *   where min1 and min2 are the two cheapest edges from each city.
 *   This is the Held-Karp style bound.
 *
 * Time  : O(n^2 * 2^n) worst case — same as brute force without pruning
 *         In practice much faster because many branches are pruned early.
 * Space : O(n^2) — adjacency matrix + recursion stack
 *
 * Practical limit: works well for n <= 15 cities.
 * ---------------------------------------------------------------
 */

#include <iostream>
#include <climits>
#include <chrono>
#include <algorithm>

using namespace std;

const int MAX = 10;

int  adj[MAX][MAX];
bool visited[MAX];
int  bestCost;

// ---- Bound Helpers ---------------------------------------------------

// Minimum edge cost leaving 'city'
int firstMin(int city, int n) {
    int mn = INT_MAX;
    for (int k = 0; k < n; k++)
        if (k != city && adj[city][k] < mn)
            mn = adj[city][k];
    return mn;
}

// Second minimum edge cost leaving 'city'
int secondMin(int city, int n) {
    int first = INT_MAX, second = INT_MAX;
    for (int k = 0; k < n; k++) {
        if (k == city) continue;
        if (adj[city][k] <= first) {
            second = first;
            first  = adj[city][k];
        } else if (adj[city][k] < second) {
            second = adj[city][k];
        }
    }
    return second;
}

// ---- Branch and Bound ------------------------------------------------

void tspBnB(int bound, int weight, int level, int path[], int n) {
    if (level == n) {
        // All cities visited; check if we can close the tour back to city 0
        if (adj[path[level - 1]][path[0]] != 0) {
            int total = weight + adj[path[level - 1]][path[0]];
            bestCost  = min(bestCost, total);
        }
        return;
    }

    for (int city = 0; city < n; city++) {
        if (adj[path[level - 1]][city] == 0 || visited[city])
            continue;

        int savedBound = bound;
        weight += adj[path[level - 1]][city];

        // Update the lower bound for this step
        if (level == 1)
            bound -= (firstMin(path[level - 1], n) + firstMin(city, n)) / 2;
        else
            bound -= (secondMin(path[level - 1], n) + firstMin(city, n)) / 2;

        // Only go deeper if the current path + bound is still promising
        if (bound + weight < bestCost) {
            path[level]   = city;
            visited[city] = true;
            tspBnB(bound, weight, level + 1, path, n);
        }

        // Backtrack: restore weight and bound, unmark visited cities
        weight -= adj[path[level - 1]][city];
        bound   = savedBound;
        fill(visited, visited + n, false);
        for (int i = 0; i < level; i++)
            visited[path[i]] = true;
    }
}

// ---- Main ------------------------------------------------------------

int main() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;

    cout << "Enter the " << n << "x" << n << " cost matrix:" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> adj[i][j];

    // Compute initial lower bound using all cities
    int initialBound = 0;
    for (int i = 0; i < n; i++)
        initialBound += (firstMin(i, n) + secondMin(i, n));
    initialBound /= 2;

    fill(visited, visited + n, false);
    bestCost    = INT_MAX;

    int path[MAX];
    path[0]      = 0;
    visited[0]   = true;

    auto start = chrono::high_resolution_clock::now();

    tspBnB(initialBound, 0, 1, path, n);

    auto stop     = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    cout << "\nMinimum TSP cost : " << bestCost << endl;
    cout << "Time             : " << dur << " microseconds" << endl;

    return 0;
}
