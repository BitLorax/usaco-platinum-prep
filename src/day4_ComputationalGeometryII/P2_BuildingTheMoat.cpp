//
// Created by WillJ on 10/4/2018.
//
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>

#define MAX_HOLECNT 5000
using namespace std;

struct Coord {
    int x, y, id;
    bool operator<(const Coord &a) const {
        if (x == a.x) return y < a.y;
        return x < a.x;
    }
    double calcDist(Coord a) { return sqrt(abs(x - a.x) * abs(x - a.x) + abs(y - a.y) * abs(y - a.y)); }
};

Coord holeLocs[MAX_HOLECNT];

int checkRotation(Coord a, Coord b, Coord c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    //ccw+, cw-
    //AB to AC
}

int main() {
    int holeCount; cin >> holeCount;
    for (int i = 0; i < holeCount; i++) {
        cin >> holeLocs[i].x >> holeLocs[i].y;
    }
    vector<Coord> hull;
    sort(holeLocs, holeLocs + holeCount);
    for (int i = 0; i < holeCount; i++) {
        Coord curr = holeLocs[i];
        while (hull.size() >= 2 && checkRotation(hull[hull.size() - 1], hull[hull.size() - 2], curr) < 0) {
            hull.pop_back();
        }
        hull.push_back(curr);
    }
    for (int i = holeCount - 1; i >= 0; i--) {
        Coord curr = holeLocs[i];
        while (hull.size() >= 2 && checkRotation(hull[hull.size() - 1], hull[hull.size() - 2], curr) < 0) {
            hull.pop_back();
        }
        hull.push_back(curr);
    }
    double dist = 0;
    for (int i = 1; i < hull.size(); i++) {
        dist += hull[i].calcDist(hull[i - 1]);
    }
    printf("%.2f", dist);
    return 0;
}
