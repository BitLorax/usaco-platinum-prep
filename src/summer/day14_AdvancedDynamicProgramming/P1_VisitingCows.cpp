//
// Created by WillJ on 7/18/2019.
//

#include <iostream>
#include <fstream>
#include <vector>

#define INF 2000000000
#define MAX_COWCNT 50000

using namespace std;

vector<int> connections[MAX_COWCNT + 1];
int DP[MAX_COWCNT + 1][2];

void dfs(int cur, int par = -1) {
    DP[cur][1] = 1;
    for (int j : connections[cur])
        if (j != par) dfs(j, cur);
    DP[par][0] += max(DP[cur][0], DP[cur][1]);
    DP[par][1] += DP[cur][0];
}

int main() {
    int cowCount; cin >> cowCount;
    for (int i = 0; i < cowCount - 1; i++) {
        int a, b; cin >> a >> b;
        connections[a].push_back(b);
        connections[b].push_back(a);
    }

    dfs(1);
    int maxVisit = 0;
    for (int i = 1; i <= cowCount; i++) maxVisit = max(maxVisit, max(DP[i][0], DP[i][1]));
    cout << maxVisit << endl;
    return 0;
}
