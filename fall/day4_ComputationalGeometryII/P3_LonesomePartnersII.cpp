//
// Created by WillJ on 10/5/2018.
//

#include <iostream>
#include <algorithm>
#include <vector>

#define MAX_COWCNT 50000

using namespace std;

struct Coord {
    int x, y, id;
    bool operator<(const Coord &a) const {
        if (x == a.x) return y < a.y;
        return x < a.x;
    }
    long long calcDist(Coord a) { return abs(x - a.x) * abs(x - a.x) + abs(y - a.y) * abs(y - a.y); }
};

Coord cowLocs[MAX_COWCNT];
vector<Coord> hull;

int checkRotation(Coord a, Coord b, Coord c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    //ccw+, cw-
    //a -> b -> c
}

int main() {
    int cowCount; cin >> cowCount;
    for (int i = 0; i < cowCount; i++) {
        cin >> cowLocs[i].x >> cowLocs[i].y;
        cowLocs[i].id = i + 1;
    }
    sort(cowLocs, cowLocs + cowCount);
    for (int i = 0; i < cowCount; i++) {
        Coord curr = cowLocs[i];
        while (hull.size() >= 2 && checkRotation(hull[hull.size() - 1], hull[hull.size() - 2], curr) < 0) hull.pop_back();
        hull.push_back(curr);
    }
    for (int i = cowCount - 1; i >= 0; i--) {
        Coord curr = cowLocs[i];
        while (hull.size() >= 2 && checkRotation(hull[hull.size() - 1], hull[hull.size() - 2], curr) < 0) hull.pop_back();
        hull.push_back(curr);
    }
    long long maxDist = 0;
    pair<int, int> farthest;
    for (int i = 0; i < hull.size(); i++) {
        for (int j = i + 1; j < hull.size(); j++) {
            if (hull[i].calcDist(hull[j]) > maxDist) {
                maxDist = hull[i].calcDist(hull[j]);
                farthest.first = min(hull[i].id, hull[j].id);
                farthest.second = max(hull[i].id, hull[j].id);
            } else if (hull[i].calcDist(hull[j]) == maxDist) {
                if (farthest.first == hull[i].id) farthest.second = min(farthest.second, hull[j].id);
                else if (i < farthest.first) {
                    farthest.first = min(hull[i].id, hull[j].id);
                    farthest.second = max(hull[i].id, hull[j].id);
                }
            }
        }
    }
    cout << farthest.first << " " << farthest.second << endl;
    return 0;
}