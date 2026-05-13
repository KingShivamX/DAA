// Practical 2.3 - Activity Selection (Greedy)
// Sort activities by finish time, greedily select non-overlapping ones.
// Always picking the earliest-finishing activity maximizes count. Time: O(n log n)

#include <bits/stdc++.h>
using namespace std;

struct Activity {
    int id, start, finish;
};

int main() {
    int n;
    cout << "Enter number of activities: ";
    cin >> n;

    vector<Activity> acts(n);
    for (int i = 0; i < n; i++) {
        acts[i].id = i + 1;
        cout << "Activity " << i + 1 << " start finish: ";
        cin >> acts[i].start >> acts[i].finish;
    }

    // Sort by finish time ascending
    sort(acts.begin(), acts.end(), [](const Activity& a, const Activity& b) {
        return a.finish < b.finish;
    });

    cout << "Selected activities: ";
    int lastFinish = -1, count = 0;
    for (auto& a : acts) {
        if (a.start >= lastFinish) {
            cout << a.id << " ";
            lastFinish = a.finish;
            count++;
        }
    }

    cout << "\nTotal selected: " << count << "\n";
    return 0;
}
