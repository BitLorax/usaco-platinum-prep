//
// Created by WillJ on 7/10/2019.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#define INF 2100000000
#define MAX_FIELDCNT 250

using namespace std;

struct Node {
    int pos, par, weight;
    bool operator<(const Node &a) const {
        return weight > a.weight;
    }
};

int fieldCount, connectionCount;
vector<pair<int, int>> connections[MAX_FIELDCNT + 1];
int dists[MAX_FIELDCNT + 1];
int par[MAX_FIELDCNT + 1];
pair<int, int> doubledEdge;

int dijkstras(bool trackPar) {
    for (int i = 0; i <= fieldCount; i++) dists[i] = INF;
    priority_queue<Node> q;
    q.push(Node{1, -1, 0});
    while (!q.empty()) {
        Node cur = q.top(); q.pop();
        if (dists[cur.pos] != INF) continue;
        dists[cur.pos] = cur.weight;
        if (trackPar) par[cur.pos] = cur.par;
        for (pair<int, int> j : connections[cur.pos]) {
            int k = ((doubledEdge.first == cur.pos || doubledEdge.first == j.first) &&
                     (doubledEdge.second == cur.pos || doubledEdge.second == j.first)) ? 2 : 1;
            q.push(Node{j.first, cur.pos, cur.weight + k * j.second});
        }
    }
    return dists[fieldCount];
}

int main() {
    cin >> fieldCount >> connectionCount;
    for (int i = 0; i < connectionCount; i++) {
        int a, b, c; cin >> a >> b >> c;
        connections[a].push_back(make_pair(b, c));
        connections[b].push_back(make_pair(a, c));
    }

    int normLen = dijkstras(true);

    int maxLen = 0;
    int curNode = fieldCount;
    while (curNode != 1) {
        doubledEdge.first = curNode; doubledEdge.second = par[curNode];
        maxLen = max(maxLen, dijkstras(false));
        curNode = par[curNode];
    }

    cout << maxLen - normLen << endl;
    return 0;
}
