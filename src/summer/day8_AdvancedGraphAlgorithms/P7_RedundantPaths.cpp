//
// Created by WillJ on 7/10/2019.
//

//BCC with tarjan
//make all points part of cycle
//connect leaves (deg 1) together = ceil(leaves / 2)

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

#define INF 2000000000
#define MAX_FIELDCNT 5000

using namespace std;

int fieldCount, pathCount;
vector<int> connections[MAX_FIELDCNT + 1];
set<int> BCCConnections[MAX_FIELDCNT + 1];

namespace tarjanSCC {
    bool inStack[MAX_FIELDCNT + 1];
    stack<int> nodes; //<bot, top>
    int in[MAX_FIELDCNT + 1], low[MAX_FIELDCNT + 1], t = 0, sccCount = 0;
    int scc[MAX_FIELDCNT + 1];

    void traverse(int cur, int par = -1) {
        low[cur] = in[cur] = ++t;
        nodes.push(cur); inStack[cur] = true;
        for (int j : connections[cur]) {
            if (in[j] == 0) {
                traverse(j, cur);
                low[cur] = min(low[cur], low[j]);
            } else if (inStack[j] && j != par) {
                low[cur] = min(low[cur], in[j]);
            }
        }
        if (low[cur] == in[cur]) { //can't go any higher, found bcc
            while (true) {
                int n = nodes.top(); nodes.pop();
                inStack[n] = false;
                scc[n] = sccCount;
                if (n == cur) break;
            }
            sccCount++;
        }
    }

    void run() {
        for (int i = 1; i <= fieldCount; i++)
            if (in[i] == 0) traverse(i);
    }
}


int main() {
    cin >> fieldCount >> pathCount;
    for (int i = 0; i < pathCount; i++) {
        int a, b; cin >> a >> b;
        connections[a].push_back(b);
        connections[b].push_back(a);
    }
    tarjanSCC::run();
    for (int i = 1; i <= fieldCount; i++) {
        for (int j : connections[i]) {
            if (tarjanSCC::scc[i] == tarjanSCC::scc[j]) continue;
            BCCConnections[tarjanSCC::scc[i]].insert(tarjanSCC::scc[j]);
            BCCConnections[tarjanSCC::scc[j]].insert(tarjanSCC::scc[i]);
        }
    }

    int leafCount = 0;
    for (int i = 0; i <= fieldCount; i++) {
        if (BCCConnections[i].size() == 1) leafCount++;
    }
    cout << ceil((double) leafCount / 2) << endl;
    return 0;
}
