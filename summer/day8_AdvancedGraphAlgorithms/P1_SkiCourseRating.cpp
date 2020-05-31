//
// Created by WillJ on 7/10/2019.
//

//union find

#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <stack>

#define INF 2000000000
#define MAX_SIDELEN 500

using namespace std;

struct Edge {
    long long a, b, weight;
    bool operator<(const Edge &u) const {
        return weight < u.weight;
    }
};

int height, width, req;
long long grid[MAX_SIDELEN + 1][MAX_SIDELEN + 1];
Edge edges[MAX_SIDELEN * MAX_SIDELEN * 2];

int component[MAX_SIDELEN * MAX_SIDELEN + 1];
long long difficulty[MAX_SIDELEN * MAX_SIDELEN + 1];
vector<int> indices[MAX_SIDELEN * MAX_SIDELEN + 1];
int startIndx[MAX_SIDELEN * MAX_SIDELEN + 1];

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
    void join(int a, int b, int weight) {
        if (indices[component[b]].size() > indices[component[a]].size()) {
            int temp = a;
            a = b; b = temp;
        }
        for (int j : indices[component[b]]) {
            component[j] = component[a];
            indices[component[a]].push_back(j);
        }
        if (indices[component[a]].size() >= req) {
            for (int j = startIndx[component[a]]; j < indices[component[a]].size(); j++) {
                difficulty[indices[component[a]][j]] = min(difficulty[indices[component[a]][j]], (long long)weight);
            }
            startIndx[component[a]] = indices[component[a]].size();
        }
    }
};

inline int toInt(int x, int y) {
    return y * width + x;
}

int main() {
    cin >> height >> width >> req;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cin >> grid[j][i];
        }
    }
    for (int i = 0; i <= height * width; i++) difficulty[i] = INF;
    int k = 0;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (i < width - 1) edges[k++] = Edge{toInt(i, j), toInt(i + 1, j), abs(grid[i][j] - grid[i + 1][j])};
            if (j < height - 1) edges[k++] = Edge{toInt(i, j), toInt(i, j + 1), abs(grid[i][j] - grid[i][j + 1])};
        }
    }
    sort(edges, edges + k);
    UnionFind uf{}; uf.construct(height * width);
    for (int i = 0; i < k; i++) {
        int a = edges[i].a, b = edges[i].b;
        if (uf.find(a) != uf.find(b)) {
            uf.join(a, b, edges[i].weight);
        }
    }

    long long sum = 0;
    for (int i = 0; i < height * width; i++) {
        int a; cin >> a;
        if (a) sum += difficulty[i];
    }

    cout << sum << endl;
    return 0;
}
