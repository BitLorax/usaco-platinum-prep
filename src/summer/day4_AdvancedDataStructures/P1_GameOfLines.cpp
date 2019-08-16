//
// Created by WillJ on 7/4/2019.
//

#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>

#define INF 2000000000
#define MAX_POINTCNT 200

using namespace std;

struct Coord {
    int x, y;
};

Coord points[MAX_POINTCNT];
set<pair<int, int>> slopes;

int main() {
    int pointCount; cin >> pointCount;
    for (int i = 0; i < pointCount; i++) {
        cin >> points[i].x >> points[i].y;
    }
    for (int i = 0; i < pointCount; i++) {
        for (int j = i + 1; j < pointCount; j++) {
            int gcd = __gcd(points[i].y - points[j].y, points[i].x - points[j].x);
            slopes.insert(make_pair((points[i].y - points[j].y) / gcd, (points[i].x - points[j].x) / gcd));
        }
    }

    cout << slopes.size() << endl;
    return 0;
}
