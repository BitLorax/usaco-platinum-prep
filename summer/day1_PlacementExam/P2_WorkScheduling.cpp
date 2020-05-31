//
// Created by WillJ on 7/1/2019.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

#define MAX_TIME 10000000

vector<pair<int, int>> jobs;

int main() {
    int jobCount; cin >> jobCount;
    for (int i = 0; i < jobCount; i++) {
        long long dTime, profit; cin >> dTime >> profit;
        jobs.push_back(make_pair(dTime, profit));
    }

    sort(jobs.begin(), jobs.end());

    long long profit = 0;
    int time = -1;
    vector<int> curJobs;
    int p = 0;
    for (int i = jobCount - 1; i >= 0; i--) {
        time = jobs[i].first;
        while (i >= 0 && jobs[i].first == time) {
            curJobs.push_back(jobs[i--].second);
        }
        i++;
        sort(curJobs.begin() + p, curJobs.end(), std::greater<int>());
        int size = curJobs.size() - p;
        for (int j = 0; (j < jobs[i].first - ((i == 0) ? 0 : jobs[i - 1].first)) && j < size; j++) {
            profit += curJobs[p++];
        }
    }

    cout << profit << endl;

    /*
    int p = jobs.size() - 1;

    vector<int> curJobs;
    long long profit = 0;
    for (int i = MAX_TIME; i > 0; i--) {
        while (i == jobs[p].first) {
            curJobs.push_back(jobs[p--].second);
        }
        if (curJobs.size() == 0) continue;
        sort(curJobs.begin(), curJobs.end(), std::greater<int>());
        auto it = curJobs.begin();
        profit += *it;
        curJobs.erase(it);
    }
     */
    return 0;
}




/*
 * struct segTree {
    void construct() {
        build(1, 0, MAX_TIME);
    }
    int build(int id, int lo, int hi) {
        if (lo == hi) {
            tree[id] = plan[lo];
            return tree[id];
        } else {
            int mid = (lo + hi) / 2;
            tree[id] = min(build(2 * id, lo, mid), build(2 * id + 1, mid + 1, hi));
        }
    }
    int query(int id, int qLo, int qHi, int lo, int hi) {
        if (qLo >= lo && qHi <= hi) return tree[id];
        else {
            int mid = (lo + hi) / 2;
            return min(query(2 * id, qLo, qHi, lo, mid), query(2 * id + 1, qLo, qHi, mid + 1, hi));
        }
    }
    int update(int id, int indx, int val, int lo, int hi) { //val is new value
        if (lo == hi) {
            tree[id] = val;
            return tree[id];
        } else {
            int mid = (lo + hi) / 2;
            tree[id] = min(update(2 * id, indx, val, lo, mid), update(2 * id + 1, indx, val, mid + 1, hi));
        }
    }
};
 */