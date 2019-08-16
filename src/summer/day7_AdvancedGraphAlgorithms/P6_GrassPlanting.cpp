//
// Created by WillJ on 7/9/2019.
//

#include <iostream>
#include <fstream>
#include <vector>

#define INF 2000000000
#define MAX_PASTURECNT 100000
#define LOG 20

using namespace std;

int k = 0;
vector<int> connections[MAX_PASTURECNT + 1];
int fPos[MAX_PASTURECNT + 1];
int subTreeSize[MAX_PASTURECNT + 1]; //inclusive

int depth[MAX_PASTURECNT + 1];
pair<int, int> pos[MAX_PASTURECNT + 1];
int up[MAX_PASTURECNT + 1][LOG + 1];

int fenwick[MAX_PASTURECNT + 1];

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
struct Fenwicks {
    int n;
    int query(int index) { //sum [0, index]
        index++;
        int ans = 0;
        for (; index > 0; index -= index&-index) ans += fenwick[index];
        return ans;
    }
    void update(int index, int add) {
        index++;
        for (; index <= n; index += index&-index) {
            fenwick[index] += add;
        }
    }
};

int dfs(int cur, int par) {
    fPos[cur] = k++;
    subTreeSize[fPos[cur]] = 1;
    for (int j : connections[cur]) {
        if (j == par) continue;
        subTreeSize[fPos[cur]] += dfs(j, cur);
    }
    return subTreeSize[fPos[cur]];
}

int main() {
    int pastureCount, queryCount; cin >> pastureCount >> queryCount;
    for (int i = 0; i < pastureCount - 1; i++) {
        int a, b; cin >> a >> b;
        connections[a].push_back(b);
        connections[b].push_back(a);
    }

    dfs(1, -1);
    LCA lca{}; lca.dfs(1, 1);
    Fenwicks f{pastureCount};
    for (int i = 0; i < queryCount; i++) {
        char a; int b, c; cin >> a >> b >> c;
        if (a == 'P') {
            int curLca = lca.query(b, c);
            f.update(fPos[curLca], ((b != curLca && c != curLca) ? -2 : -1));
            if (b != curLca) f.update(fPos[b], 1);
            if (c != curLca) f.update(fPos[c], 1);
        } else {
            int edge = max(fPos[b], fPos[c]);
            cout << f.query(edge + subTreeSize[edge] - 1) - f.query(edge - 1) << endl;
        }
    }
    return 0;
}
