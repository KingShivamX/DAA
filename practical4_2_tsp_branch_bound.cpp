// Practical 4.2 - Travelling Salesman Problem (Branch and Bound)
// Prune search tree using a lower bound estimated from minimum edge costs.
// Explores fewer paths than brute force by discarding unpromising branches.

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;
int adj[MAXN][MAXN];
bool visited[MAXN];
int finalMin = INT_MAX;

// Minimum edge cost leaving a city
int firstMin(int city, int n) {
    int mn = INT_MAX;
    for (int k = 0; k < n; k++)
        if (adj[city][k] < mn && city != k)
            mn = adj[city][k];
    return mn;
}

// Second minimum edge cost leaving a city
int secondMin(int city, int n) {
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < n; j++) {
        if (city == j) continue;
        if (adj[city][j] <= first) { second = first; first = adj[city][j]; }
        else if (adj[city][j] < second) second = adj[city][j];
    }
    return second;
}

void solve(int bound, int weight, int level, int path[], int n) {
    if (level == n) {
        if (adj[path[level - 1]][path[0]] != 0) {
            int total = weight + adj[path[level - 1]][path[0]];
            finalMin = min(finalMin, total);
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        if (adj[path[level - 1]][i] != 0 && !visited[i]) {
            int tempBound = bound;
            weight += adj[path[level - 1]][i];

            // Update lower bound estimate
            tempBound -= (level == 1)
                ? (firstMin(path[level - 1], n) + firstMin(i, n)) / 2
                : (secondMin(path[level - 1], n) + firstMin(i, n)) / 2;

            if (tempBound + weight < finalMin) {
                path[level] = i;
                visited[i]  = true;
                solve(tempBound, weight, level + 1, path, n);
            }

            // Backtrack
            weight -= adj[path[level - 1]][i];
            visited[i] = false;
        }
    }
}

int main() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;

    cout << "Enter cost matrix (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> adj[i][j];

    // Initial lower bound: sum of (min1 + min2) / 2 for each city
    int bound = 0;
    for (int i = 0; i < n; i++)
        bound += (firstMin(i, n) + secondMin(i, n));
    bound /= 2;

    fill(visited, visited + n, false);
    int path[MAXN];
    path[0]      = 0;
    visited[0]   = true;

    solve(bound, 0, 1, path, n);

    cout << "Min cost: " << finalMin << "\n";
    return 0;
}
