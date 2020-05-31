//
// Created by WillJ on 7/10/2019.
//

//log and bellman ford

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#define INF 2000000000000000
#define MAX_COUNTRYCNT 2000
#define MAX_CONNECTIONCNT 25000

using namespace std;

struct Edge {
    int a, b;
    long double weight;
};

long long countryCount, connectionCount, s, e;
Edge connections[MAX_CONNECTIONCNT + 1];
long double dists[MAX_COUNTRYCNT + 1];

bool bellmanFord(int start, double weight) {
    for (int i = 0; i <= countryCount; i++) dists[i] = INF;
    dists[start] = weight;
    for (int i = 1; i <= countryCount; i++) {
        for (int j = 0; j < connectionCount; j++) {
            Edge cur = connections[j];
            if (dists[cur.a] != INF) dists[cur.b] = min(dists[cur.b], dists[cur.a] * cur.weight);
        }
    }
    for (int i = 0; i < connectionCount; i++) {
        Edge cur = connections[i];
        if (dists[cur.a] != INF && dists[cur.a] * cur.weight < dists[cur.b]) return false;
    }
    return true;
}

int main() {
    long double startVal; cin >> countryCount >> connectionCount >> startVal >> s >> e;
    for (int i = 0; i < connectionCount; i++) {
        cin >> connections[i].a >> connections[i].b >> connections[i].weight;
    }
    if (!bellmanFord(s, startVal)) {
        cout << 0 << endl;
    } else {
        cout << (long long)(dists[e]) << endl;
    }
    return 0;
}
