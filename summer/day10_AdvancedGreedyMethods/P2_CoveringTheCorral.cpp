//
// Created by WillJ on 7/12/2019.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>

#define INF 2000000000
#define MAX_COVERCNT 100000

using namespace std;

struct RMQ {
    long long n;
    vector<vector<long long>> maxs;
    void preprocess(long long arr[], long long size) {
        n = size;
        maxs = vector<vector<long long>>(n + 1, vector<long long>((long long)(ceil(log2(n)) + 1), 0));

        for (long long i = 0; i < n; i++) maxs[i][0] = i;
        for (long long j = 1; (1 << j) <= n; j++) {
            for (long long i = 0; (i + (1 << j)) <= n; i++) {
                if (arr[maxs[i][j - 1]] > arr[maxs[i + (1 << (j - 1))][j - 1]]) maxs[i][j] = maxs[i][j - 1];
                else maxs[i][j] = maxs[i + (1 << (j - 1))][j - 1];
            }
        }
    }
    long long query(long long arr[], long long lo, long long hi) {
        long long i = (long long)(log2(hi - lo + 1));
        if (arr[maxs[lo][i]] >= arr[maxs[hi - (1 << i) + 1][i]]) return maxs[lo][i];
        return maxs[hi - (1 << i) + 1][i];
    }
};

pair<long long, long long> covers[MAX_COVERCNT + 1];
long long s[MAX_COVERCNT + 1];
long long e[MAX_COVERCNT + 1];
bool used[MAX_COVERCNT + 1];

int main() {
    long long circumference, coverCount; cin >> circumference >> coverCount;
    for (long long i = 0; i < coverCount; i++) {
        cin >> covers[i].first >> covers[i].second;
    }
    sort(covers, covers + coverCount);
    for (long long i = 0; i < coverCount; i++) {
        s[i] = covers[i].first;
        e[i] = s[i] + covers[i].second;
    }
    RMQ rmq{}; rmq.preprocess(e, coverCount);

    int minUsed = INF;
    for (int i = 0; s[i] <= e[coverCount - 1] - circumference; i++) {
        if (used[i]) continue;
        used[i] = true;
        queue<long long> covers;
        covers.push(i);
        long long curCover = i, taken = 0, start = s[curCover], end = e[curCover];
        while (end < circumference) {
            long long lo = upper_bound(s, s + coverCount, start) - s;
            long long hi = (upper_bound(s, s + coverCount, end) - s) - 1;
            long long optimal = rmq.query(e, lo, hi);

            covers.push(optimal);
            curCover = optimal;
            taken++;
            start = s[curCover];
            end = e[curCover];
            used[curCover] = true;
        }
        end -= circumference;
        while (end >= s[covers.front()] && end <= e[covers.front()]) covers.pop();
        minUsed = min(minUsed, (int)covers.size() + 1);
    }

    cout << minUsed << endl;
    return 0;
}
