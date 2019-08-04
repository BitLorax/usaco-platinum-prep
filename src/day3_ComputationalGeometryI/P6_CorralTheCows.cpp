//
// Created by WillJ on 9/28/2018.
//
#include <iostream>
#include <algorithm>
#include <set>

#define MAX_CLOVERCNT 500

using namespace std;

struct Coord {
    int x, y;
    bool operator<(const Coord &a) const {
        if (x == a.x) return y < a.y;
        return x < a.x;
    }
};

Coord cloverLocs[MAX_CLOVERCNT];
int maxX, maxY, cloverCount, cloverMin;

bool test(int sideLen) {
    int rightX = 0;
    for (int leftX = 0; leftX < cloverCount; leftX++) {
        while (rightX + 1 < cloverCount && abs(cloverLocs[leftX].x - cloverLocs[rightX + 1].x) + 1 <= sideLen) rightX++;

        int top = leftX;
        int cloverIn = 1;
        for (int bot = leftX; bot < rightX; bot++) {
            while (top + 1 <= rightX && abs(cloverLocs[bot].y - cloverLocs[top + 1].y) + 1 <= sideLen) {
                cloverIn++;
                top++;
            }
            if (cloverIn >= cloverMin) return true;
            cloverIn--;
        }
    }
    return false;
}

int main() {
    cin >> cloverMin >> cloverCount;
    for (int i = 0; i < cloverCount; i++) {
        cin >> cloverLocs[i].x >> cloverLocs[i].y;
        maxX = max(maxX, cloverLocs[i].x);
        maxY = max(maxY, cloverLocs[i].y);
    }
    sort(cloverLocs, cloverLocs + cloverCount);
    int lo = 0; int hi = 10010; int mid = -1;
    while (lo < hi) {
        mid = (lo + hi) / 2;
        if (test(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    cout << lo << endl;
    return 0;
}
