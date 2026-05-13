// Practical 3.5 - Floyd-Warshall All-Pairs Shortest Path (Dynamic Programming)
// For each intermediate vertex k, relax all (i, j) paths through k.
// Time: O(V^3) | Works with negative edges (no negative cycles).

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;

    vector<vector<int>> dist(n, vector<int>(n));
    cout << "Enter adjacency matrix (-1 for no edge):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cin >> dist[i][j];
            if (dist[i][j] == -1) dist[i][j] = INF;
        }

    // Relax distances through each intermediate vertex k
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] != INF && dist[k][j] != INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    cout << "Shortest distance matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << (dist[i][j] == INF ? "INF" : to_string(dist[i][j])) << "\t";
        cout << "\n";
    }
    return 0;
}
