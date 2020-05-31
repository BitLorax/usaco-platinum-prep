//
// Created by WillJ on 7/8/2019.
//

#include <iostream>
#include <fstream>
#include <vector>

#define INF 2000000000
#define MAX_POINTCNT 100000
#define POWER 20

using namespace std;

int getMax(int a, int b) { return max(a, b); }
int getSum(int a, int b) { return a + b; }

struct SegTree {
    int n, id;
    vector<int> segTree = vector<int>(1 << POWER);
    vector<int> lazy = vector<int>(1 << POWER);
    /**
     * Sets up segment tree in O(N)
     *
     * @param arr Array to be processed
     * @param size Size of array
     */
    void construct(int arr[], int size, int id, int node = 1, int a = 0, int b = -1) {
        if (b == -1) {
            n = size;
            b = n - 1;
            this->id = id;
        }

        if (a > b) return;
        if (a == b) {
            segTree[node] = arr[a];
            return;
        }
        construct(arr, size, id, node * 2, a, (a + b) / 2);
        construct(arr, size, id, node * 2 + 1, (a + b) / 2 + 1, b);
        segTree[node] = (id) ? getMax(segTree[node * 2], segTree[node * 2 + 1]) : getSum(segTree[node * 2], segTree[node * 2 + 1]);
    }
    /**
     * Updates value of index in O(logN)
     *
     * @param index Index to update
     * @param add Value to add to array
     */
    void update(int i, int val, int node = 1, int a = 0, int b = -1) {
        if (b == -1) b = n - 1;
        if (a > i || b < i) return;
        if (a >= i && b <= i) {
            segTree[node] = val;
            return;
        }
        update(i, val, node * 2, a, (a + b) / 2);
        update(i, val, node * 2 + 1, (a + b) / 2 + 1, b);
        segTree[node] = (id) ? getMax(segTree[node * 2], segTree[node * 2 + 1]) : getSum(segTree[node * 2], segTree[node * 2 + 1]);
    }
    /**
     * Queries the segment tree for the sum of [from, to] in O(logN)
     *
     * @param from Lower index
     * @param to Higher index
     * @return sum of values in array [from, to]
     */
    int query(int i, int j, int node = 1, int a = 0, int b = -1) {
        if (b == -1) b = n -1;
        if (a > b || a > j || b < i) return 0;
        if (a >= i && b <= j) return segTree[node];
        int one = query(i, j, node * 2, a, (a + b) / 2);
        int two = query(i, j, node * 2 + 1, (a + b) / 2 + 1, b);
        return (id) ? getMax(one, two) : getSum(one, two);
    }
private:
    void push(int node, int a, int b) {
        if (lazy[node] != 0) {
            segTree[node] += (b - a) * lazy[node];
            if (a != b) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }
};
struct Coord {
    int x, y;
};

inline int getDist(Coord a, Coord b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}
inline int getConserve(Coord a, Coord b, Coord c) {
    return (getDist(a, b) + getDist(b, c)) - getDist(a, c);
}

Coord points[MAX_POINTCNT + 1];
int startDists[MAX_POINTCNT + 1]; //[i] = distance from i to i + 1
int startConserve[MAX_POINTCNT + 1];

int main() {
    int pointCount, queryCount; cin >> pointCount >> queryCount;
    for (int i = 0; i < pointCount; i++)
        cin >> points[i].x >> points[i].y;
    for (int i = 0; i < pointCount - 1; i++)
        startDists[i] = getDist(points[i], points[i + 1]);
    for (int i = 1; i < pointCount - 1; i++)
        startConserve[i] = getConserve(points[i - 1], points[i], points[i + 1]);

    SegTree dists{}; dists.construct(startDists, pointCount - 1, 0);
    SegTree conserve{}; conserve.construct(startConserve, pointCount - 1, 1);
    for (int i = 0; i < queryCount; i++) {
        char a; cin >> a;
        if (a == 'Q') {
            int b, c; cin >> b >> c;
            b--; c--;
            int dist = dists.query(b, c- 1);
            int maxConserve = conserve.query(b + 1, c - 1);
            cout << dist - maxConserve << endl;
        } else {
            int b; cin >> b;
            b--;
            cin >> points[b].x >> points[b].y;
            if (b > 0) {
                dists.update(b - 1, getDist(points[b - 1], points[b]));
            }
            if (b < pointCount - 1) {
                dists.update(b, getDist(points[b + 1], points[b]));
            }
            if (b > 1) {
                conserve.update(b - 1, getConserve(points[b - 2], points[b - 1], points[b]));
            }
            if (b < pointCount - 2) {
                conserve.update(b + 1, getConserve(points[b], points[b + 1], points[b + 2]));
            }
            if (b > 0 && b < pointCount - 1) {
                conserve.update(b, getConserve(points[b - 1], points[b], points[b + 1]));
            }
        }
    }
    return 0;
}
