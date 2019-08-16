//
// Created by WillJ on 9/16/2018.
//
#include <iostream>
#define INF 2000000000
#define MAX_PLOTCNT 5000

using namespace std;

int DP[MAX_PLOTCNT + 10];
int positions[MAX_PLOTCNT + 10];

double getSlope(int from, int to) {
    return double(positions[to] - positions[from]) / (to - from);
}

int main() {
    int plotCount, maxDist; cin >> plotCount >> maxDist;
    for (int i = 0 ; i < plotCount; i++) {
        cin >> positions[i];
    }
    DP[0] = 1;
    for (int i = 1; i < plotCount; i++) DP[i] = INF;
    for (int i = 0; i < plotCount; i++) {
        double maxSlope = -INF;
        for (int to = i + 1; to <= i + maxDist && to < plotCount; to++) {
            double slope = getSlope(i, to);
            if (slope >= maxSlope) {
                maxSlope = slope;
                DP[to] = min(DP[to], DP[i] + 1);
            }
        }
    }
    cout << DP[plotCount - 1] << endl;
    return 0;
}

