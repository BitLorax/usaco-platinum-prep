//
// Created by WillJ on 7/12/2019.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define INF 2000000000
#define MAX_FIELDCNT 100000
#define MAX_QUERYCNT 10000

using namespace std;

long long dT = 0;
vector<pair<long long, long long>> connections[MAX_FIELDCNT + 1];
long long cows[MAX_FIELDCNT + 1];
pair<long long, long long> times[MAX_QUERYCNT + 1];
long long ans[MAX_QUERYCNT + 1];

void dfs(long long cur, long long par = -1, long long lim = -1) {
    for (pair<long long, long long> j : connections[cur]) {
        dfs(j.first, cur, j.second);
    }

    if (cur == 1) return;
    long long move = min(cows[cur], dT * lim);
    cows[par] += move;
    cows[cur] -= move;
}

int main() {
    long long fieldCount, queryCount; cin >> fieldCount >> queryCount;
    for (long long i = 2; i <= fieldCount; i++) {
        long long a, b, c; cin >> a >> b >> c;
        connections[a].emplace_back(i, c);
        cows[i] = b;
    }
    for (long long i = 0; i < queryCount; i++) {
        cin >> times[i].first;
        times[i].second = i;
    }
    sort(times, times + queryCount);
    long long prevT = 0;
    for (long long i = 0; i < queryCount; i++) {
        dT = times[i].first - prevT;
        dfs(1);
        ans[times[i].second] = cows[1];
        prevT = times[i].first;
    }

    for (long long i = 0; i < queryCount; i++) cout << ans[i] << endl;
    return 0;
}
