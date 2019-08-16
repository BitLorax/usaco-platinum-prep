//
// Created by WillJ on 7/12/2019.
//

#include <iostream>
#include <fstream>
#include <algorithm>

#define INF 2000000000
#define MAX_STALLCNT 100000
#define MAX_REQCNT 100000
#define POWER 20

using namespace std;

struct Req {
    int a, b;
    bool operator<(const Req &u) const {
        if (b == u.b) return (b - a) < (u.b - u.a);
        return b < u.b;
    }
};


int segTree[1 << POWER];
int lazy[1 << POWER];

struct SegTree {
    int n;
    void construct(int arr[], int size, int node = 1, int a = 0, int b = -1) {
        n = size;
        if (b == -1) b = n - 1;

        if (a > b) return;
        if (a == b) {
            segTree[node] = arr[a];
            return;
        }
        construct(arr, size, node * 2, a, (a + b) / 2);
        construct(arr, size, node * 2 + 1, (a + b) / 2 + 1, b);
        segTree[node] = func(segTree[node * 2], segTree[node * 2 + 1]);
    }
    void update(int i, int j, int val, int node = 1, int a = 0, int b = -1) {
        if (b == -1) b = n - 1;
        push(node, a, b);
        if (a > j || b < i) return;
        if (a >= i && b <= j) {
            lazy[node] += val;
            push(node, a, b);
            return;
        }
        update(i, j, val, node * 2, a, (a + b) / 2);
        update(i, j, val, node * 2 + 1, (a + b) / 2 + 1, b);
        segTree[node] = func(segTree[node * 2], segTree[node * 2 + 1]);
    }
    int query(int i, int j, int node = 1, int a = 0, int b = -1) {
        if (b == -1) b = n -1;
        push(node, a, b);
        if (a > b || a > j || b < i) return INF;
        if (a >= i && b <= j) return segTree[node];
        int one = query(i, j, node * 2, a, (a + b) / 2);
        int two = query(i, j, node * 2 + 1, (a + b) / 2 + 1, b);
        return func(one, two);
    }
private:
    void push(int node, int a, int b) {
        if (lazy[node] != 0) {
            segTree[node] += lazy[node];
            if (a != b) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }
    int func(int a, int b) {
        return min(a, b);
    }
};


int capacity[MAX_STALLCNT + 1];
Req requests[MAX_REQCNT + 1];

int main() {
    int stallCount, reqCount; cin >> stallCount >> reqCount;
    for (int i = 0; i < stallCount; i++) {
        cin >> capacity[i];
    }
    for (int i = 0; i < reqCount; i++) {
        cin >> requests[i].a >> requests[i].b;
        requests[i].a--; requests[i].b--;
    }
    sort(requests, requests + reqCount);
    int satisfied = 0;
    SegTree st{stallCount}; st.construct(capacity, stallCount);
    for (int i = 0; i < reqCount; i++) {
        Req cur = requests[i];
        if (st.query(cur.a, cur.b) > 0) {
            satisfied++;
            st.update(cur.a, cur.b, -1);
        }
    }

    cout << satisfied << endl;
    return 0;
}
