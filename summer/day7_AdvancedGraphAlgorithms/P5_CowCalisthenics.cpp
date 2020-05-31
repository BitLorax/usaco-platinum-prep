//
// Created by WillJ on 7/9/2019.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define INF 2000000000
#define MAX_VERTEXCNT 100000

using namespace std;

int lenLim = -1, cuts = 0;
vector<int> connections[MAX_VERTEXCNT + 1];

inline int dfs(int cur, int par) {
    vector<int> subTrees;
    subTrees.push_back(0);
    for (int j : connections[cur]) {
        if (j == par) continue;
        subTrees.push_back(dfs(j, cur));
    }
    sort(subTrees.begin(), subTrees.end());
    int i = subTrees.size() - 1;
    for (; i > 0; i--) {
        if (subTrees[i] + subTrees[i - 1] <= lenLim) break;
        cuts++;
    }
    return subTrees[i] + 1;
}

int main() {
    int vertexCount, blockLim; cin >> vertexCount >> blockLim;
    for (int i = 0; i < vertexCount - 1; i++) {
        int a, b; cin >> a >> b;
        connections[a].push_back(b);
        connections[b].push_back(a);
    }

    int lo = 0, hi = vertexCount - 1;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        lenLim = mid, cuts = 0;
        dfs(1, -1);
        if (cuts > blockLim) lo = mid + 1;
        else hi = mid;
    }

    cout << lo << endl;
    return 0;
}
