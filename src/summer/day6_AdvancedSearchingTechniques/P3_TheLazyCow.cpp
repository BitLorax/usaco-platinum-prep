//
// Created by WillJ on 7/8/2019.
//

//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

#define INF 2000000000
#define MAX_GRASSCNT 100000
#define POWER 20

using namespace std;

struct Grass {
    long long x, y, weight;
};
struct vSide {
    long long x, y1, y2, mag, weight;
    bool operator<(const vSide &a) const {
        return x < a.x;
    }
};

long long segTree[1 << POWER];
long long lazy[1 << POWER];

struct SegTree {
    long long n;
    void update(long long i, long long j, long long val, long long node = 1, long long a = 0, long long b = -1) {
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
    long long query(long long i, long long j, long long node = 1, long long a = 0, long long b = -1) {
        if (b == -1) b = n -1;
        push(node, a, b);
        if (a > b || a > j || b < i) return 0;
        if (a >= i && b <= j) return segTree[node];
        long long one = query(i, j, node * 2, a, (a + b) / 2);
        long long two = query(i, j, node * 2 + 1, (a + b) / 2 + 1, b);
        return func(one, two);
    }
private:
    void push(long long node, long long a, long long b) {
        if (lazy[node] != 0) {
            segTree[node] += lazy[node];
            if (a != b) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }
    long long func(long long a, long long b) {
        return max(a, b);
    }
};

vSide vSides[MAX_GRASSCNT * 2 + 1];
int yVals[MAX_GRASSCNT * 2 + 1];
pair<long long, long long> vSideLoc[MAX_GRASSCNT + 1];
map<int, int> mp;

int main() {
    long long grassCount, len; cin >> grassCount >> len;
    for (long long i = 0; i < grassCount; i++) {
        long long w, x, y; cin >> w >> x >> y;
        int newX = x + y, newY = x - y;
        vSides[i] = vSide{newX + len + 1, newY - len, newY + len, -1, w};
        vSides[i + grassCount] = vSide{newX - len, newY - len, newY + len, 1, w};
        yVals[i] = newY - len;
        yVals[i + grassCount] = newY + len;
    }
    sort(vSides, vSides + 2 * grassCount);
    sort(yVals, yVals + 2 * grassCount);
    for (int i = 0; i < 2 * grassCount; i++) mp[yVals[i]] = -1;
    for (int i = 0; i < 2 * grassCount; i++) {
        if (mp[yVals[i]] == -1) mp[yVals[i]] = i;
    }


    SegTree st{2 * grassCount};
    long long maxGain = 0;
    for (long long i = 0; i < grassCount * 2; i++) {
        long long curX = vSides[i].x;
        while (i < grassCount * 2 && curX == vSides[i].x) {
            st.update(mp[vSides[i].y1], mp[vSides[i].y2], vSides[i].mag * vSides[i].weight);
            i++;
        }
        i--;
        maxGain = max(maxGain, (long long)st.query(0, grassCount * 2 - 1));
    }

    cout << maxGain << endl;
    return 0;
}
