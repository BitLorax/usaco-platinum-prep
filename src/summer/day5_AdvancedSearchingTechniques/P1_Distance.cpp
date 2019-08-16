//
// Created by WillJ on 7/5/2019.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#define MAX_NODECNT 100000
#define LOG 20

using namespace std;

int nodeCount, queryCount, l;
vector<int> connections[MAX_NODECNT + 1];

int counter = 0;
int up[MAX_NODECNT + 1][LOG];
pair<int, int> pos[MAX_NODECNT + 1];
int depth[MAX_NODECNT + 1];

void dfs(int cur, int par) {
    depth[cur] = depth[par] + 1;
    pos[cur].first = counter++;
    up[cur][0] = par;
    for (int i = 1; i <= l; i++) {
        up[cur][i] = up[up[cur][i - 1]][i - 1];
    }
    for (int j : connections[cur]) {
        if (j != par) dfs(j, cur);
    }
    pos[cur].second = counter++;
};
bool isAncestor(int a, int b) { //a is ancestor of b?
    return pos[b].first >= pos[a].first && pos[b].second <= pos[a].second;
}
int query(int a, int b) {
    if (isAncestor(a, b)) return a;
    if (isAncestor(b, a)) return b;
    for (int i = l; i >= 0; i--) {
        if (!isAncestor(up[a][i], b)) {
            a = up[a][i];
        }
    }
    return up[a][0];
}

int main() {
    cin >> nodeCount >> queryCount;
    l = ceil(log2(nodeCount));

    for (int i = 0; i < nodeCount - 1; i++) {
        int a, b; cin >> a >> b;
        connections[a].push_back(b);
        connections[b].push_back(a);
    }

    depth[1] = 1;
    dfs(1, 1);
    for (int i = 0; i < queryCount; i++) {
        int a, b; cin >> a >> b;
        int curLca = query(a, b);
        cout << (depth[a] - depth[curLca]) + (depth[b] - depth[curLca]) << endl;
    }
    return 0;
}
