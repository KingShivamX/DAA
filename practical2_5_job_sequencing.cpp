// Practical 2.5 - Job Sequencing with Deadlines (Greedy)
// Sort jobs by profit descending, assign each to the latest free slot before its deadline.
// Maximizes total profit. Time: O(n^2)

#include <bits/stdc++.h>
using namespace std;

struct Job {
    char id;
    int deadline, profit;
};

int main() {
    int n;
    cout << "Enter number of jobs: ";
    cin >> n;

    vector<Job> jobs(n);
    for (int i = 0; i < n; i++) {
        cout << "Job " << i + 1 << " id deadline profit: ";
        cin >> jobs[i].id >> jobs[i].deadline >> jobs[i].profit;
    }

    // Sort by profit descending
    sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
        return a.profit > b.profit;
    });

    int maxD = 0;
    for (auto& j : jobs) maxD = max(maxD, j.deadline);

    vector<char> slots(maxD, '-');
    vector<bool> occupied(maxD, false);
    int totalProfit = 0, count = 0;

    for (auto& j : jobs) {
        // Find latest free slot before deadline
        for (int t = j.deadline - 1; t >= 0; t--) {
            if (!occupied[t]) {
                occupied[t] = true;
                slots[t] = j.id;
                totalProfit += j.profit;
                count++;
                break;
            }
        }
    }

    cout << "Job sequence: ";
    for (int i = 0; i < maxD; i++)
        if (occupied[i]) cout << slots[i] << " ";
    cout << "\nJobs done: " << count << "\nTotal profit: " << totalProfit << "\n";
    return 0;
}
