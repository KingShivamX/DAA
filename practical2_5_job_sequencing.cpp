/*
 * Job Sequencing with Deadlines (Greedy Algorithm)
 *
 * ---------------------------------------------------------------
 * Schedule jobs (each taking 1 unit of time) to maximize total
 * profit. Each job has a deadline — it must be finished by then.
 *
 * Strategy: Sort jobs by profit (descending). For each job, assign
 *           it to the latest available time slot before its deadline.
 *
 * Time  : O(n^2)    — for each job, scan slots from deadline to 1
 *         (Can be improved to O(n log n) with Union-Find)
 * Space : O(n)      — slot array
 * ---------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

struct Job {
    char id;
    int  deadline;
    int  profit;
};

// ---- Core Algorithm --------------------------------------------------

void jobSequencing(vector<Job>& jobs) {
    // Sort jobs by profit, highest first
    sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
        return a.profit > b.profit;
    });

    // Find the maximum deadline to know how many time slots we need
    int maxDeadline = 0;
    for (const Job& j : jobs)
        maxDeadline = max(maxDeadline, j.deadline);

    // slot[t] = id of job assigned to time slot t+1; '-' means empty
    vector<char> slot(maxDeadline, '-');
    vector<bool> filled(maxDeadline, false);

    int totalProfit = 0;
    int count       = 0;

    for (const Job& job : jobs) {
        // Try to fit this job in the latest free slot before its deadline
        for (int t = job.deadline - 1; t >= 0; t--) {
            if (!filled[t]) {
                slot[t]   = job.id;
                filled[t] = true;
                totalProfit += job.profit;
                count++;
                break;
            }
        }
    }

    cout << "\nJob sequence    : ";
    for (int t = 0; t < maxDeadline; t++)
        if (filled[t]) cout << slot[t] << " ";
    cout << endl;

    cout << "Jobs scheduled  : " << count << endl;
    cout << "Total profit    : " << totalProfit << endl;
}

// ---- Main ------------------------------------------------------------

int main() {
    int n;
    cout << "Enter number of jobs: ";
    cin >> n;

    vector<Job> jobs(n);
    cout << "Enter job ID, deadline, and profit for each job:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  Job " << i + 1 << " (id deadline profit): ";
        cin >> jobs[i].id >> jobs[i].deadline >> jobs[i].profit;
    }

    auto start = chrono::high_resolution_clock::now();

    jobSequencing(jobs);

    auto stop     = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    cout << "Time            : " << dur << " microseconds" << endl;

    return 0;
}
