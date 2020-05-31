//
// Created by WillJ on 7/8/2019.
//

#include <iostream>
#include <fstream>

#define INF 2000000000
#define MAX_STALLCNT 100000
#define POWER 1 << 20

using namespace std;

int segTree[POWER];
bool lazy[POWER];

    int n;
    void push(int node, int a, int b) {
        if (lazy[node]) {
            segTree[node] = (b - a + 1) - segTree[node];
            if (a != b) {
                lazy[node * 2] = !lazy[node * 2];
                lazy[node * 2 + 1] = !lazy[node * 2 + 1];
            }
            lazy[node] = false;
        }
    }
    void change(int node, int a, int b, int i, int j) {
        push(node, a, b);
        if (a > j || b < i) return;
        if (a >= i && b <= j) {
            lazy[node] = true;
            push(node, a, b);
            return;
        }
        change(node * 2, a, (a + b) / 2, i, j);
        change(node * 2 + 1, (a + b) / 2 + 1, b, i, j);
        segTree[node] = segTree[node * 2] + segTree[node * 2 + 1];
    }
    int ask(int node, int a, int b, int i, int j) {
        push(node, a, b);
        if (a > j || b < i) return 0;
        if (a >= i && b <= j) return segTree[node];
        int one = ask(node * 2, a, (a + b) / 2, i, j);
        int two = ask(node * 2 + 1, (a + b) / 2 + 1, b, i, j);
        return one + two;
    }

    void update(int lo, int hi) {
        change(1, 0, n - 1, lo, hi);
    }
    int query(int from, int to) {
        return ask(1, 0, n - 1, from, to);
    }



int main() {
    int stallCount, commandCount; cin >> stallCount >> commandCount;
    n = stallCount;
    for (int i = 0; i < commandCount; i++) {
        int a, b, c; cin >> a >> b >> c;
        b--; c--;
        if (a == 0) update(b, c);
        else {
            int d = query(b, c);
            cout << d << endl;
        }
    }
    return 0;
}
