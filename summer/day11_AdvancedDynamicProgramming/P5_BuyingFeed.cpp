//
// Created by WillJ on 7/15/2019.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>
#include <deque>

#define INF 2000000000
#define f first
#define s second
#define MAX_FEEDREQ 10000
#define MAX_STORECNT 500
#define POWER 15

using namespace std;

struct Store {
    long long loc, stock, cost;
    bool operator<(const Store &a) const {
        return loc < a.loc;
    }
};

Store stores[MAX_STORECNT + 1];
long long DP[2][MAX_FEEDREQ + 1];

int main() {
    long long feedReq, len, storeCount; cin >> feedReq >> len >> storeCount;
    for (long long i = 0; i < storeCount; i++) {
        cin >> stores[i].loc >> stores[i].stock >> stores[i].cost;
    }
    sort(stores, stores + storeCount);

    long long prevLoc = 0;
    for (long long i = 0; i < storeCount; i++) {
        deque<pair<long long, long long>> dq;
        for (long long k = 0; k <= feedReq; k++) {
            long long f = (i ? DP[(i - 1) % 2][k] : (k ? INF : 0)) + (stores[i].loc - prevLoc) * k * k - k * stores[i].cost;
            long long s = k + stores[i].stock;

            while (!dq.empty() && dq.back().f > f) dq.pop_back();
            dq.emplace_back(f, s);
            while (!dq.empty() && dq.front().s < k) dq.pop_front();

            if (!dq.empty()) DP[i % 2][k] = dq.front().f + k * stores[i].cost;
            else DP[i % 2][k] = INF;
        }
        prevLoc = stores[i].loc;
    }

    cout << DP[(storeCount - 1) % 2][feedReq] + feedReq * feedReq * (len - stores[storeCount - 1].loc) << endl;
    return 0;
}
