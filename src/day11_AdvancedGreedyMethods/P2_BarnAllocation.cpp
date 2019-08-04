//
// Created by WillJ on 12/2/2018.
//

#include <iostream>
#include <algorithm>

#define INF 2000000000
#define MAX_STALLCNT 100000
#define MAX_REQUESTCNT 100000

using namespace std;

int stallInfo[MAX_STALLCNT];
pair<int, int> requestInfo[MAX_REQUESTCNT];
int segTree[1000000];
int lazy[1000000];

int segQuery(int node, int a, int b, int i, int j) {
    //[[i, j]
    // 0-index query
    //segQuery(1, 0, N - 1, i, j)
    if (a > b || a > j || b < i) return INF; //change as necessary

    if (lazy[node] != 0) {
        segTree[node] += lazy[node];
        if (a != b) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }

    if (a >= i && b <= j) return segTree[node];
    int one = segQuery(node * 2, a, (a + b) / 2, i, j);
    int two = segQuery(node * 2 + 1, (a + b) / 2 + 1, b, i, j);
    return min(one, two); //change  as necessary
}
void segUpdate(int node, int a, int b, int i, int j, int val) {
    //[[i, j]
    // 0-index query
    //segUpdate(1, 0, N - 1, i, j)
    if (lazy[node] != 0) {
        segTree[node] += lazy[node];
        if (a != b) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }

    if (a > b || a > j || b < i) return;
    if (a >= i && b <= j) { //completely within [i, j]
        segTree[node] += val;
        if (a != b) {
            lazy[node * 2] += val;
            lazy[node * 2 + 1] += val;
        }
        return;
    }
    segUpdate(node * 2, a, (a + b) / 2, i, j, val);
    segUpdate(node * 2 + 1, (a + b) / 2 + 1, b, i, j, val);
    segTree[node] = min(segTree[node * 2], segTree[node * 2 + 1]);
}
void segBuild(int node, int a, int b) {
    //segBuild(1, 0, N - 1)
    if (a > b) return;
    if (a == b) {
        segTree[node] = stallInfo[a];
        return;
    }
    segBuild(node * 2, a, (a + b) / 2);
    segBuild(node * 2 + 1, (a + b) / 2 + 1, b);
    segTree[node] = min(segTree[node * 2], segTree[node * 2 + 1]); //defines what this segTree contains
}
int main() {
    int stallCount, requestCount; cin >> stallCount >> requestCount;
    for (int i = 0; i < stallCount; i++) cin >> stallInfo[i];
    for (int i = 0; i < requestCount; i++) {
        cin >> requestInfo[i].second >> requestInfo[i].first; //sort by end
        requestInfo[i].first--; requestInfo[i].second--;
    }
    sort(requestInfo, requestInfo + requestCount);
    segBuild(1, 0, stallCount - 1);
    int requestsAccepted = 0;
    for (int i = 0; i < requestCount; i++) {
        if (segQuery(1, 0, stallCount - 1, requestInfo[i].second, requestInfo[i].first) > 0) {
            requestsAccepted++;
            segUpdate(1, 0, stallCount - 1, requestInfo[i].second, requestInfo[i].first, -1);
        }
    }
    cout << requestsAccepted << endl;
    return 0;
}
