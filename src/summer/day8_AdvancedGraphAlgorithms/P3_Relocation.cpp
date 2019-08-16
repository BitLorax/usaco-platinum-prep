//
// Created by WillJ on 7/10/2019.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 2000000000
#define MAX_TOWNCNT 10000
#define MAX_MARKETCNT 5

using namespace std;

struct Node {
    int pos, weight;
    bool operator<(const Node &a) const {
        return weight > a.weight;
    }
};

int townCount, connectionCount, marketCount;
vector<pair<int, int>> connections[MAX_TOWNCNT + 1];
int id[MAX_TOWNCNT + 1];
int dists[MAX_MARKETCNT + 1][MAX_TOWNCNT + 1];
int minDists[MAX_TOWNCNT + 1];

void dijkstras(int start) {
    for (int i = 0; i <= townCount; i++)
        dists[id[start]][i] = INF;

    priority_queue<Node> q;
    q.push(Node{start, 0});
    while (!q.empty()) {
        Node cur = q.top(); q.pop();
        if (dists[id[start]][cur.pos] != INF) continue;
        dists[id[start]][cur.pos] = cur.weight;
        for (pair<int, int> j : connections[cur.pos]) {
            q.push(Node{j.first, cur.weight + j.second});
        }
    }
}

int main() {
    cin >> townCount >> connectionCount >> marketCount;
    vector<int> markets;
    for (int i = 0; i < marketCount; i++) {
        int a; cin >> a;
        id[a] = i + 1;
        markets.push_back(a);
    }
    for (int i = 0; i < connectionCount; i++) {
        int a, b, c; cin >> a >> b >> c;
        connections[a].push_back(make_pair(b, c));
        connections[b].push_back(make_pair(a, c));
    }
    for (int i = 0; i <= townCount; i++) minDists[i] = INF;
    for (int i : markets) dijkstras(i);
    do {
        int midDist = 0;
        for (int i = 0; i < marketCount - 1; i++) {
            midDist += dists[id[markets[i]]][markets[i + 1]];
        }
        for (int j = 1; j <= townCount; j++) {
            if (id[j] > 0) continue;
            minDists[j] = min(minDists[j], midDist + dists[id[markets[0]]][j] + dists[id[markets[marketCount - 1]]][j]);
        }
    } while (next_permutation(markets.begin(), markets.end()));

    int minDist = INF;
    for (int i = 1; i <= townCount; i++) minDist = min(minDist, minDists[i]);

    cout << minDist << endl;
    return 0;
}
