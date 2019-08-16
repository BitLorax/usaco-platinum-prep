//
// Created by WillJ on 7/9/2019.
//

#include <iostream>
#include <fstream>
#include <vector>

#define INF 1e16
#define MAX_BARNCNT 100000

using namespace std;

long long barnCount, cowCount = 0;
long long size[MAX_BARNCNT + 1];
vector<pair<long long, long long>> connections[MAX_BARNCNT + 1];
long long botSize[MAX_BARNCNT + 1]; //inclusive
long long topSize[MAX_BARNCNT + 1]; //exclusive
long long botLen[MAX_BARNCNT + 1];
long long topLen[MAX_BARNCNT + 1];

long long calcSizes(long long cur, long long par) {
    botSize[cur] += size[cur];
    for (pair<long long, long long> j : connections[cur]) {
        if (j.first == par) continue;
        botSize[cur] += calcSizes(j.first, cur);
    }
    topSize[cur] = cowCount - botSize[cur];
    return botSize[cur];
}

long long calcBotLen(long long cur, long long par) {
    for (pair<long long, long long> j : connections[cur]) {
        if (j.first == par) continue;
        botLen[cur] += j.second * botSize[j.first] + calcBotLen(j.first, cur);
    }
    return botLen[cur];
}
long long calcTopLen(long long cur, long long par, long long len) {
    if (cur != 0) {
        long long top = topLen[par] + topSize[par] * len;
        long long bot = botLen[par] - (botLen[cur] + botSize[cur] * len) + ((botSize[par] - botSize[cur]) * len);
        topLen[cur] = top + bot;
    }
    for (pair<long long, long long> j : connections[cur]) {
        if (j.first == par) continue;
        calcTopLen(j.first, cur, j.second);
    }
}

int main() {
    cin >> barnCount;
    for (long long i = 0; i < barnCount; i++) {
        cin >> size[i];
        cowCount += size[i];
    }
    for (long long i = 0; i < barnCount - 1; i++) {
        long long a, b, c; cin >> a >> b >> c;
        a--; b--;
        connections[a].push_back(make_pair(b, c));
        connections[b].push_back(make_pair(a, c));
    }

    calcSizes(0, -1);
    calcBotLen(0, -1);
    calcTopLen(0, -1, -1);

    long long minDist = INF;
    for (long long i = 0; i < barnCount; i++) {
        minDist = min(minDist, topLen[i] + botLen[i]);
    }

    cout << minDist << endl;
    return 0;
}
