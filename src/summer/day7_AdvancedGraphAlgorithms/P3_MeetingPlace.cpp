//
// Created by WillJ on 7/9/2019.
//

#include <iostream>
#include <fstream>
#include <vector>

#define INF 2000000000
#define MAX_PASTURECNT 1000
#define LOG 12

using namespace std;

vector<int> connections[MAX_PASTURECNT + 1];
int depth[MAX_PASTURECNT + 1];
pair<int, int> pos[MAX_PASTURECNT + 1];
int up[MAX_PASTURECNT + 1][LOG + 1];

struct LCA  {
    int counter = 0;
    void dfs(int cur, int par) {
        depth[cur] = depth[par] + 1;
        pos[cur].first = counter++;

        up[cur][0] = par;
        for (int i = 1; i <= LOG; i++)
            up[cur][i] = up[up[cur][i - 1]][i - 1];
        for (int j : connections[cur])
            if (j != par) dfs(j, cur);

        pos[cur].second = counter++;
    };
    bool isAncestor(int a, int b) {
        return pos[b].first >= pos[a].first && pos[b].second <= pos[a].second;
    }
    int query(int a, int b) {
        if (isAncestor(a, b)) return a;
        if (isAncestor(b, a)) return b;
        for (int i = LOG; i >= 0; i--)
            if (!isAncestor(up[a][i], b)) a = up[a][i];
        return up[a][0];
    }
};

int main() {
    int pastureCount, queryCount; cin >> pastureCount >> queryCount;
    for (int i = 2; i <= pastureCount; i++) {
        int a; cin >> a;
        connections[a].push_back(i);
    }
    LCA lca{}; lca.dfs(1, 1);
    for (int i = 0; i < queryCount; i++) {
        int a, b; cin >> a >> b;
        cout << lca.query(a, b) << endl;
    }
    return 0;
}
