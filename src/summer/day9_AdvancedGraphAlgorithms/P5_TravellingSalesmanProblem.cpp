//
// Created by WillJ on 7/11/2019.
//

#include <iostream>
#include <fstream>
#include <vector>

#define INF 2000000000
#define MAX_TOWNCNT 20

using namespace std;

int DP[1 << (MAX_TOWNCNT)][MAX_TOWNCNT + 1];
int connections[MAX_TOWNCNT + 1][MAX_TOWNCNT + 1];

int main() {
    int townCount, roadCount; cin >> townCount >> roadCount;
    for (int i = 0; i < roadCount; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        connections[a][b] = connections[b][a] = c;
    }

    for (int i = 0; i <= (1 << townCount); i++)
        for (int j = 0; j < townCount; j++) DP[i][j] = INF;
    for (int j = 0; j < townCount; j++)
        DP[(1 << j)][j] = 0;

    for (int i = 1; i < (1 << townCount); i++) {
        for (int j = 0; j < townCount; j++) {
            if ((i & (1 << j)) == 0) continue;
            for (int k = 0; k < townCount; k++) {
                if (connections[k][j] == 0) continue;
                DP[i][j] = min(DP[i][j], DP[i ^ (1 << j)][k] + connections[k][j]);
            }
        }
    }

    int minDist = INF;
    for (int i = 0; i < townCount; i++) minDist = min(minDist, DP[(1 << townCount) - 1][i]);
    cout << minDist << endl;

    return 0;
}
