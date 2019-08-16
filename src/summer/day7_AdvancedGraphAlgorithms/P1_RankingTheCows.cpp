//
// Created by WillJ on 7/9/2019.
//

//transitive closure

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

#define INF 2000000000
#define MAX_COWCNT 1000

using namespace std;

vector<int> connections[MAX_COWCNT + 1];
bool totalConnections[MAX_COWCNT + 1][MAX_COWCNT + 1];
bool visited[MAX_COWCNT + 1];

void dfs(int origin, int cur) {
    if (visited[cur]) return;
    visited[cur] = true;
    totalConnections[origin][cur] = totalConnections[cur][origin] = true;
    for (int j : connections[cur]) {
        dfs(origin, j);
    }
}

int main() {
    int cowCount, connectionCount; cin >> cowCount >> connectionCount;
    for (int i = 0; i < connectionCount; i++) {
        int a, b; cin >> a >> b;
        connections[a].push_back(b);
    }
    for (int i = 1; i <= cowCount; i++) {
        for (int j = 1; j <= cowCount; j++) visited[j] = false;
        dfs(i, i);
    }
    int ans = 0;
    for (int i = 1; i <= cowCount; i++) {
        for (int j = i + 1; j <= cowCount; j++) {
            if (!totalConnections[i][j]) ans++;
        }
    }

    cout << ans << endl;
    return 0;
}
