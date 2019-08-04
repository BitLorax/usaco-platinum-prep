//
// Created by WillJ on 11/25/2018.
//

#include <iostream>

#define INF 2000000000
#define MAX_STALLCNT 100000


using namespace std;

int segTree[7000000];
bool lazy[7000000];

void segUpdate(int node, int a, int b, int i, int j) {
    //[[i, j]
    // 0-index query
    //segUpdate(1, 0, N - 1, i, j)
    if (lazy[node]) {
        segTree[node] = (b - a + 1) - segTree[node]; //flip
        if (a != b) {
            lazy[node * 2] = !lazy[node * 2];
            lazy[node * 2 + 1] = !lazy[node * 2 + 1];
        }
        lazy[node] = false;
    }

    if (a > b || a > j || b < i) return;
    if (a >= i && b <= j) { //completely within [i, j]
        segTree[node] = (b - a + 1) - segTree[node]; //flip
        if (a != b) {
            lazy[node * 2] = !lazy[node * 2];
            lazy[node * 2 + 1] = !lazy[node * 2 + 1];
        }
        return;
    }
    segUpdate(node * 2, a, (a + b) / 2, i, j);
    segUpdate(node * 2 + 1, (a + b) / 2 + 1, b, i, j);
    segTree[node] = segTree[node * 2] + segTree[node * 2 + 1]; //sum the lights
}

int segQuery(int node, int a, int b, int i, int j) {
    //[[i, j]
    // 0-index query
    //segQuery(1, 0, N - 1, i, j)
    if (a > b || a > j || b < i) return 0; //change as necessary

    if (lazy[node]) {
        segTree[node] = (b - a + 1) - segTree[node]; //flip
        if (a != b) {
            lazy[node * 2] = !lazy[node * 2];
            lazy[node * 2 + 1] = !lazy[node * 2 + 1];
        }
        lazy[node] = false;
    }

    if (a >= i && b <= j) return segTree[node];
    int one = segQuery(node * 2, a, (a + b) / 2, i, j);
    int two = segQuery(node * 2 + 1, (a + b) / 2 + 1, b, i, j);
    return one + two; //change  as necessary
}

int main() {
    int stallCount, operationCount; cin >> stallCount >> operationCount;
    for (int i = 0; i < operationCount; i++) {
        int t, lo, hi; cin >> t >> lo >> hi;
        lo--; hi--;
        if (t == 0) {
            segUpdate(1, 0, stallCount - 1, lo, hi);
        } else {
            cout << segQuery(1, 0, stallCount - 1, lo, hi) << endl;
        }
    }
    return 0;
}