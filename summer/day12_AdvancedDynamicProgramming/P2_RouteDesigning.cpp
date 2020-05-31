
//
// Created by WillJ on 7/16/2019.
//

#include <iostream>
#include <fstream>
#include <algorithm>

#define INF 2000000000
#define MAX_SITECNT 40000
#define MAX_PATHCNT 100000

using namespace std;

struct Path {
    int ls, rs;
    bool operator<(const Path &a) const {
        return ls + rs < a.ls + a.rs;
    }
};

int l[MAX_SITECNT + 1];
int r[MAX_SITECNT + 1];
Path paths[MAX_PATHCNT + 1];
int lDP[MAX_SITECNT + 1];
int rDP[MAX_SITECNT + 1];

int main() {
    int leftCount, rightCount, pathCount; cin >> leftCount >> rightCount >> pathCount;
    for (int i = 0; i < leftCount; i++) {
        cin >> l[i];
        lDP[i] = l[i];
    }
    for (int i = 0; i < rightCount; i++) {
        cin >> r[i];
        rDP[i] = r[i];
    }
    for (int i = 0; i < pathCount; i++) {
        cin >> paths[i].ls >> paths[i].rs;
        paths[i].ls--; paths[i].rs--;
    }

    sort(paths, paths + pathCount);
    for (int i = 0; i < pathCount; i++) {
        Path cur = paths[i];
        int a = lDP[cur.ls], b = rDP[cur.rs];
        lDP[cur.ls] = max(lDP[cur.ls], b + l[cur.ls]);
        rDP[cur.rs] = max(rDP[cur.rs], a + r[cur.rs]);
    }

    int maxVal = 0;
    for (int i = 0; i < leftCount; i++) maxVal = max(maxVal, lDP[i]);
    for (int i = 0; i < rightCount; i++) maxVal = max(maxVal, rDP[i]);

    cout << maxVal << endl;
    return 0;
}
