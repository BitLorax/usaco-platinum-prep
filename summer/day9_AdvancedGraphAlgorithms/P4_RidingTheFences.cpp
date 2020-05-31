//
// Created by WillJ on 7/11/2019.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define INF 2000000000
#define MAX_INTERSECTCNT 500
#define MAX_FENCECNT 1024

using namespace std;

vector<pair<int, int>> connections[MAX_INTERSECTCNT + 1];
int edges[MAX_INTERSECTCNT + 1];
int indx[MAX_INTERSECTCNT + 1];
bool used[MAX_FENCECNT + 1];
vector<int> tour;

void dfs(int cur) {
    for (indx[cur]; indx[cur] < connections[cur].size(); indx[cur]++) {
        if (used[connections[cur][indx[cur]].second]) {
            continue;
        }
        used[connections[cur][indx[cur]].second] = true;
        dfs(connections[cur][indx[cur]].first);
    }
    tour.push_back(cur);
}

int main() {

    int fenceCount; cin >> fenceCount;
    for (int i = 0; i < fenceCount; i++) {
        int a, b; cin >> a >> b;
        connections[a].emplace_back(b, i);
        connections[b].emplace_back(a, i);
        edges[a]++; edges[b]++;
    }
    for (int i = 1; i <= MAX_INTERSECTCNT; i++) {
        sort(connections[i].begin(), connections[i].end());
    }
    for (int i = 1; i <= MAX_INTERSECTCNT; i++) {
        if (edges[i] % 2 == 1) {
            dfs(i);
            break;
        }
    }
    if (tour.size() == 0) {
        for (int i = 1; i <= MAX_INTERSECTCNT; i++) {
            if (edges[i] > 0) {
                dfs(i);
                break;
            }
        }
    }
    for (int j = tour.size() - 1; j >= 0; j--) {
        cout << tour[j] << endl;
    }
    return 0;
}
