//
// Created by WillJ on 7/10/2019.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define INF 2000000000
#define MAX_PASTURECNT 10000
#define MAX_PATHCNT 100000

using namespace std;

struct Edge {
    int a, b, weight;
    bool operator<(const Edge &u) const {
        return weight < u.weight;
    }
};

int component[MAX_PASTURECNT + 1];
vector<int> indices[MAX_PATHCNT + 1];

struct UnionFind {
    int n;
    void construct(int size) {
        n = size;
        for (int i = 0; i <= n; i++) {
            component[i] = i;
            indices[i].push_back(i);
        }
    }
    int find(int node) {
        return component[node];
    }
    void join(int a, int b) {
        if (indices[component[b]].size() > indices[component[a]].size()) {
            int temp = a;
            a = b; b = temp;
        }
        for (int j : indices[component[b]]) {
            component[j] = component[a];
            indices[component[a]].push_back(j);
        }
    }
};

int pastureCount, pathCount;
int cost[MAX_PASTURECNT + 1];
Edge edges[MAX_PATHCNT + 1];

int kruskals() {
    UnionFind unionFind{}; unionFind.construct(pastureCount + 1);
    sort(edges, edges + pathCount);

    int total = 0;
    for (Edge cur : edges) {
        if (unionFind.find(cur.a) != unionFind.find(cur.b)) {
            unionFind.join(cur.a, cur.b);
            total += cur.weight;
        }
    }
    return total;
}

int main() {
    cin >> pastureCount >> pathCount;
    int minCost = INF;
    for (int i = 1; i <= pastureCount; i++) {
        cin >> cost[i];
        minCost = min(minCost, cost[i]);
    }
    for (int i = 0; i < pathCount; i++) {
        cin >> edges[i].a >> edges[i].b;
        int c; cin >> c;
        edges[i].weight = 2 * c + cost[edges[i].a] + cost[edges[i].b];
    }

    cout << kruskals() + minCost << endl;
    return 0;
}
