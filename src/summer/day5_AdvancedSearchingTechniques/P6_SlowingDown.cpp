//
// Created by WillJ on 7/5/2019.
//

#include <iostream>
#include <fstream>
#include <vector>

#define INF 2000000000
#define MAX_PASTURECNT 100000

using namespace std;

long long fenwick[MAX_PASTURECNT + 1];
struct Fenwicks {
    int query(int index) {
        index++;
        int ans = 0;
        for (; index > 0; index -= index&-index) ans += fenwick[index];
        return ans;
    }
    void update(int index, int add) {
        index++;
        for (; index <= MAX_PASTURECNT; index += index&-index) {
            fenwick[index] += add;
        }
    }
};

vector<int> connections[MAX_PASTURECNT + 1];
long long order[MAX_PASTURECNT + 1];
long long ans[MAX_PASTURECNT + 1];
Fenwicks f{};

void dfs(int cur, int par) {
    ans[order[cur]] = f.query(order[cur]);
    f.update(order[cur], 1);
    for (int j : connections[cur]) {
        if (j != par) dfs(j, cur);
    }
    f.update(order[cur], -1);
}

int main() {
    int pastureCount; cin >> pastureCount;
    for (int i = 0; i < pastureCount - 1; i++) {
        int a, b; cin >> a >> b;
        connections[a].push_back(b);
        connections[b].push_back(a);
    }
    for (int i = 1; i <= pastureCount; i++) {
        int a; cin >> a;
        order[a] = i;
    }

    dfs(1, -1);
    for (int i = 1; i <= pastureCount; i++) cout << ans[i] << endl;
    return 0;
}