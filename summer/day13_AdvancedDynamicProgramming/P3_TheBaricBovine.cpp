//
// Created by WillJ on 7/17/2019.
//

#include <iostream>
#include <fstream>

#define INF 2000000000
#define MAX_N 100

using namespace std;

int data[MAX_N + 1];
int cost[MAX_N + 1][MAX_N + 1];
int DP[MAX_N + 1][MAX_N + 1];

int main() {
    int n, e; cin >> n >> e;
    for (int i = 0; i < n; i++) {
        cin >> data[i];
    }
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = i + 1; k < j; k++)
                cost[i][j] += abs(2 * data[k] - (data[i] + data[j]));

    for (int i = 0; i < n; i++)
        for (int k = 1; k <= n; k++)
            DP[i][k] = INF;

    for (int i = 0; i < n; i++) {
        for (int k = 1; k <= i + 1; k++) {
            if (k == 1) {
                DP[i][k] = 0;
                for (int j = 0; j < i; j++) DP[i][k] += 2 * abs(data[j] - data[i]);
            } else {
                for (int j = i - 1; j >= 0; j--)
                    DP[i][k] = min(DP[i][k], DP[j][k - 1] + cost[j][i]);
            }
        }
    }

    pair<int, int> ans; ans.second = INF;
    for (int k = 1; k <= n; k++) {
        for (int i = 0; i < n; i++) {
            if (DP[i][k] == INF) continue;
            for (int j = i + 1; j < n; j++) DP[i][k] += 2 * abs(data[j] - data[i]);
            if (DP[i][k] <= e)
                ans.first = k; ans.second = min(ans.second, DP[i][k]);
        }
        if (ans.first != 0) break;
    }
    cout << ans.first << " " << ans.second << endl;
    return 0;
}
