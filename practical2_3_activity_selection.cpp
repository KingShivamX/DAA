/*
 * Activity Selection Problem (Greedy Algorithm)
 *
 * ---------------------------------------------------------------
 * Select the maximum number of non-overlapping activities from a
 * set where each activity has a start and finish time.
 *
 * Strategy: Sort by finish time. Always pick the next activity
 *           that starts after (or at) the last selected finish time.
 *
 * Time  : O(n log n)  — dominated by sorting by finish time
 * Space : O(n)        — activity list
 * ---------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

struct Activity {
    int id;
    int start;
    int finish;
};

// ---- Core Algorithm --------------------------------------------------

vector<Activity> selectActivities(vector<Activity>& activities) {
    // Sort by finish time so we always free up the timeline as early as possible
    sort(activities.begin(), activities.end(), [](const Activity& a, const Activity& b) {
        return a.finish < b.finish;
    });

    vector<Activity> selected;

    // The first activity (earliest finish) is always selected
    selected.push_back(activities[0]);

    for (int i = 1; i < (int)activities.size(); i++) {
        // Select this activity only if it starts after the last selected one finishes
        if (activities[i].start >= selected.back().finish)
            selected.push_back(activities[i]);
    }

    return selected;
}

// ---- Main ------------------------------------------------------------

int main() {
    int n;
    cout << "Enter number of activities: ";
    cin >> n;

    vector<Activity> activities(n);
    cout << "Enter start and finish time for each activity:" << endl;
    for (int i = 0; i < n; i++) {
        activities[i].id = i + 1;
        cout << "  Activity " << i + 1 << " (start finish): ";
        cin >> activities[i].start >> activities[i].finish;
    }

    auto start = chrono::high_resolution_clock::now();

    vector<Activity> selected = selectActivities(activities);

    auto stop     = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    cout << "\nSelected Activities:" << endl;
    for (const Activity& a : selected)
        cout << "  Activity " << a.id << "  [" << a.start << ", " << a.finish << "]" << endl;

    cout << "\nTotal selected : " << selected.size() << endl;
    cout << "Time           : " << dur << " microseconds" << endl;

    return 0;
}
