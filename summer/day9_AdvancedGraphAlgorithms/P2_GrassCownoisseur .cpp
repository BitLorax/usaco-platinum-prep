//
// Created by WillJ on 7/11/2019.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

#define INF 2000000000000000
#define MAX_FIELDCNT 100000

using namespace std;

long long fieldCount, pathCount;
vector<long long> connections[MAX_FIELDCNT + 1];
vector<long long> sccForward[MAX_FIELDCNT + 1];
vector<long long> sccBack[MAX_FIELDCNT + 1];
long long size[MAX_FIELDCNT + 1];

namespace tarjanSCC {
    bool inStack[MAX_FIELDCNT + 1];
    stack<long long> nodes; //<bot, top>
    long long in[MAX_FIELDCNT + 1], low[MAX_FIELDCNT + 1], t = 0, sccCount = 0;
    long long scc[MAX_FIELDCNT + 1];

    void traverse(long long cur) {
        low[cur] = in[cur] = ++t;
        nodes.push(cur); inStack[cur] = true;
        for (long long j : connections[cur]) {
            if (in[j] == 0) {
                traverse(j);
                low[cur] = min(low[cur], low[j]);
            } else if (inStack[j]) {
                low[cur] = min(low[cur], in[j]);
            }
        }
        if (low[cur] == in[cur]) { //can't go any higher, found bcc
            while (true) {
                long long n = nodes.top(); nodes.pop();
                inStack[n] = false;
                scc[n] = sccCount;
                size[sccCount]++;
                if (n == cur) break;
            }
            sccCount++;
        }
    }

    void run() {
        for (long long i = 1; i <= fieldCount; i++)
            if (in[i] == 0) traverse(i);
    }
}

long long fromRoot[MAX_FIELDCNT + 1];
long long toRoot[MAX_FIELDCNT + 1];

int main() {
    cin >> fieldCount >> pathCount;
    for (long long i = 0; i < pathCount; i++) {
        long long a, b; cin >> a >> b;
        connections[a].push_back(b);
    }
    tarjanSCC::run();
    for (long long i = 1; i <= fieldCount; i++) {
        for (long long j : connections[i]) {
            long long ii = tarjanSCC::scc[i];
            long long jj = tarjanSCC::scc[j];
            if (ii == jj) continue;
            sccForward[ii].push_back(jj);
            sccBack[jj].push_back(ii);
        }
    }
    for (long long i = 0; i <= fieldCount; i++) fromRoot[i] = toRoot[i] = -INF;
    long long root = tarjanSCC::scc[1];
    fromRoot[root] = toRoot[root] = size[root];
    for (long long i = root - 1; i >= 0; i--) {
        for (long long j : sccBack[i])
            if (j <= root) fromRoot[i] = max(fromRoot[i], fromRoot[j] + size[i]);
    }
    for (long long i = root + 1; i < tarjanSCC::sccCount; i++) {
        for (long long j : sccForward[i])
            if (j >= root) toRoot[i] = max(toRoot[i], toRoot[j] + size[i]);
    }
    long long maxDist = 0;
    for (long long i = 0; i <= root; i++) {
        for (long long j : sccBack[i]) {
            if (j < root) continue;
            maxDist = max(maxDist, fromRoot[i] + toRoot[j] - size[root]);
        }
    }

    cout << maxDist << endl;
    return 0;
}
