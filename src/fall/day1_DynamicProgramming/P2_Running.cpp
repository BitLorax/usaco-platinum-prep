//
// Created by Will Liang on 9/9/2018.
//
#include <iostream>

#define INF 2000000000
#define MAX_TIMELEN 10000
#define MAX_TIRED 500

using namespace std;

int dists[MAX_TIMELEN + 10];
int DP[MAX_TIMELEN + 1  ][MAX_TIRED + 1];

int main() {
    int timeLen, maxTired; cin >> timeLen >> maxTired;
    for (int i = 1 ; i <= timeLen; i++) {
        cin >> dists[i];
    }
    for (int i = 1; i <= timeLen; i++) {
        DP[i][0] = max(DP[i - 1][0], DP[i - 1][0]);
        int k = 1;
        while (true) {
            if (i - k < 0) break;
            if (k > (i - k)) break;
            DP[i][0] = max(DP[i][0], DP[i - k][k]);
            k++;
        }
        for (int j = 1; j <= maxTired; j++) {
            if (j > i) continue;
            DP[i][j] = DP[i - 1][j - 1] + dists[i];
        }
    }
    cout << DP[timeLen][0] << endl;
    return 0;
}


