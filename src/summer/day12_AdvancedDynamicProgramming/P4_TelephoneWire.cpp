//
// Created by WillJ on 7/16/2019.
//

#include <iostream>
#include <fstream>
#include <queue>
#include <set>

#define INF 2000000000
#define MAX_POLECNT 100000
#define MAX_HEIGHT 100

using namespace std;

int heights[MAX_POLECNT + 1];
int DP[2][MAX_HEIGHT + 1];

int main() {
    int poleCount, cost; cin >> poleCount >> cost;
    for (int i = 0; i < poleCount; i++) {
        cin >> heights[i];
    }
    for (int k = 0; k <= MAX_HEIGHT; k++) {
        DP[0][k] = DP[1][k] = INF;
    }


    for (int k = heights[0]; k <= MAX_HEIGHT; k++) {
        DP[0][k] = (k - heights[0]) * (k - heights[0]);
    }
    for (int i = 1; i < poleCount; i++) {
        multiset<int> lower; //inclusive
        multiset<int> higher;
        for (int k = heights[i - 1]; k < heights[i]; k++)
            lower.insert(DP[(i - 1) % 2][k] - cost * k);
        for (int k = heights[i]; k <= MAX_HEIGHT; k++)
            higher.insert(DP[(i - 1) % 2][k] + cost * k);
        for (int k = 0; k <= MAX_HEIGHT; k++) DP[i % 2][k] = INF;
        for (int k = heights[i]; k <= MAX_HEIGHT; k++) {
            lower.insert(DP[(i - 1) % 2][k] - cost * k);
            higher.erase(higher.find(DP[(i - 1) % 2][k] + cost * k));
            DP[i % 2][k] = (k - heights[i]) * (k - heights[i]) +
                           min(*lower.begin() + cost * k, (higher.empty() ? INF : *higher.begin() - cost * k));
        }
    }

    int minCost = INF;
    for (int i = heights[poleCount - 1]; i <= MAX_HEIGHT; i++) minCost = min(minCost, DP[(poleCount - 1) % 2][i]);
    cout << minCost << endl;
    return 0;
}
