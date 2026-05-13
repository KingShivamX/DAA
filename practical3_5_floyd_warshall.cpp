/*
 * Floyd-Warshall All-Pairs Shortest Path (Dynamic Programming)
 *
 * ---------------------------------------------------------------
 * Finds shortest paths between every pair of vertices in a
 * weighted directed graph.
 *
 * Key idea: for each intermediate vertex k, check if routing
 *   through k gives a shorter path between every pair (i, j).
 *   dist[i][j] = min(dist[i][j],  dist[i][k] + dist[k][j])
 *
 * Time  : O(V^3)  — three nested loops over all vertices
 * Space : O(V^2)  — distance matrix
 *
 * Handles negative edge weights but NOT negative-weight cycles.
 * Input: -1 in the matrix means no direct edge (treated as INF).
 * ---------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

const int INF = 1e9;

// ---- Core Algorithm --------------------------------------------------

void floydWarshall(vector<vector<int>>& dist, int V) {
    // For each intermediate vertex k, relax all (i, j) pairs
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                // Only update if both segments of the path actually exist
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

// ---- Main ------------------------------------------------------------

int main() {
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;

    // Initialise: INF everywhere, 0 on the diagonal
    vector<vector<int>> dist(V, vector<int>(V, INF));
    for (int i = 0; i < V; i++)
        dist[i][i] = 0;

    cout << "Enter the " << V << "x" << V << " adjacency matrix"
         << " (-1 means no direct edge):" << endl;

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            int val;
            cin >> val;
            if (i != j && val != -1)
                dist[i][j] = val;
        }
    }

    auto start = chrono::high_resolution_clock::now();

    floydWarshall(dist, V);

    auto stop     = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    cout << "\nAll-Pairs Shortest Path Matrix:" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                cout << "INF\t";
            else
                cout << dist[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "\nTime: " << dur << " microseconds" << endl;

    return 0;
}
