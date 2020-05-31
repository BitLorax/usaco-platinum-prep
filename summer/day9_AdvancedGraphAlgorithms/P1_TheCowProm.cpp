//
// Created by WillJ on 7/11/2019.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>

#define INF 2000000000
#define MAX_COWCNT 10000

using namespace std;

int cowCount, ropeCount;
vector<int> connections[MAX_COWCNT + 1];

namespace tarjanSCC {
    bool inStack[MAX_COWCNT + 1];
    stack<int> nodes; //<bot, top>
    int in[MAX_COWCNT + 1], low[MAX_COWCNT + 1], t = 0, sccCount = 0;
    vector<int> scc[MAX_COWCNT + 1];

    bool biconnected(int a, int b) {
        for (int j : scc[a])
            if (binary_search(scc[b].begin(), scc[b].end(), j)) return true;
        return false;
    }

    void traverse(int cur) {
        low[cur] = in[cur] = ++t;
        nodes.push(cur); inStack[cur] = true;
        for (int j : connections[cur]) {
            if (in[j] == 0) {
                traverse(j);
                low[cur] = min(low[cur], low[j]);
            } else if (inStack[j]) {
                low[cur] = min(low[cur], in[j]);
            }
        }
        if (low[cur] == in[cur]) { //can't go any higher, found bcc
            while (true) {
                int n = nodes.top(); nodes.pop();
                inStack[n] = false;
                scc[sccCount].push_back(n);
                if (n == cur) break;
            }
            sccCount++;
        }
    }

    void run() {
        for (int i = 1; i <= cowCount; i++)
            if (in[i] == 0) traverse(i);
    }
}

int main() {
    cin >> cowCount >> ropeCount;
    for (int i = 0; i < ropeCount; i++) {
        int a, b; cin >> a >> b;
        connections[a].push_back(b);
    }
    tarjanSCC::run();
    int ans = 0;
    for (int i = 0; i <= cowCount; i++)
        if (tarjanSCC::scc[i].size() > 1) ans++;
    cout << ans << endl;
    return 0;
}
