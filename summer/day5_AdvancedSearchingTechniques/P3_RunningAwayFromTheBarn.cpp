//
// Created by WillJ on 7/5/2019.
//

//

#include <iostream>
#include <fstream>
#include <vector>
#include <set>

#define INF 2000000000
#define MAX_PASTURECNT 200000
#define LOG 20

using namespace std;

long long pastureCount, lim;
vector<int> children[MAX_PASTURECNT + 1];
int parent[MAX_PASTURECNT + 1];
int jump[MAX_PASTURECNT + 1][LOG];
long long dists[MAX_PASTURECNT + 1]; //from 1 to i

long long sum[MAX_PASTURECNT + 1];

void traverse(int cur) {
    jump[cur][0] = parent[cur];
    for (int l = 1; l < LOG; l++) jump[cur][l] = jump[jump[cur][l - 1]][l - 1];
    int to = cur;
    for (int l = LOG - 1; l >= 0; l--) {
        if (jump[to][l] != 0 && dists[cur] - dists[jump[to][l]] <= lim) {
            to = jump[to][l];
        }
    }
    sum[cur]++; sum[parent[to]]--;
    for (int j : children[cur]) traverse(j);
}

int main() {
    cin >> pastureCount >> lim;
    for (int i = 2; i <= pastureCount; i++) {
        long long a, b; cin >> a >> b;
        parent[i] = a;
        children[a].push_back(i);
        dists[i] = dists[parent[i]] + b;
    }
    parent[1] = 0;

    traverse(1);
    for (int i = pastureCount; i >= 0; i--) {
        sum[parent[i]] += sum[i];
    }
    for (int i = 1; i <= pastureCount; i++) {
        cout << sum[i] << endl;
        //cout << dists[i] << endl;
    }
    return 0;
}
