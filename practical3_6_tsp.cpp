// Practical 3.6 - Travelling Salesman Problem (DP + Bitmask)
// dp[mask][i] = min cost to visit all cities in 'mask', currently at city i.
// Time: O(2^n * n^2) | Space: O(2^n * n) | Supports up to ~15 cities.

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAXN = 15;

int n;
int dist[MAXN][MAXN];
int dp[1 << MAXN][MAXN];
int nxt[1 << MAXN][MAXN]; // next city in optimal path

int tsp(int mask, int cur) {
    if (mask == (1 << n) - 1) return dist[cur][0]; // all visited, return to start
    if (dp[mask][cur] != -1)   return dp[mask][cur];

    int best = INF;
    for (int i = 0; i < n; i++) {
        if (!(mask & (1 << i)) && dist[cur][i] != INF) {
            int cost = dist[cur][i] + tsp(mask | (1 << i), i);
            if (cost < best) {
                best = cost;
                nxt[mask][cur] = i;
            }
        }
    }
    return dp[mask][cur] = best;
}

int main() {
    cout << "Enter number of cities (max " << MAXN << "): ";
    cin >> n;

    cout << "Enter distance matrix (-1 for no direct path):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cin >> dist[i][j];
            if (dist[i][j] == -1) dist[i][j] = INF;
        }

    memset(dp,  -1, sizeof(dp));
    memset(nxt, -1, sizeof(nxt));

    int minCost = tsp(1, 0);
    cout << "Min cost: " << minCost << "\n";

    // Print optimal path
    cout << "Path: 0";
    int mask = 1, cur = 0;
    while (nxt[mask][cur] != -1) {
        int next = nxt[mask][cur];
        cout << " -> " << next;
        mask |= (1 << next);
        cur = next;
    }
    cout << " -> 0\n";
    return 0;
}
