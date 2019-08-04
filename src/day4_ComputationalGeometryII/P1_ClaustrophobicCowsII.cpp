//
// Created by WillJ on 9/30/2018.
//
#include <iostream>
#include <set>
#include <algorithm>

#define INF 2000000000
#define MAX_COWCNT 50000

using namespace std;

struct Coord {
    int x, y, id;
    bool operator<(const Coord &a) const {
        if (y == a.y) return x < a.x;
        return y < a.y;
    }
    int calcDist(Coord a) { return abs(x - a.x) * abs(x - a.x) + abs(y - a.y) * abs(y - a.y); }
};
bool byX(Coord a, Coord b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

Coord cowLocs[MAX_COWCNT];

int main() {
    int cowCount; cin >> cowCount;
    for (int i = 0; i < cowCount; i++) {
        cin >> cowLocs[i].x >> cowLocs[i].y;
        cowLocs[i].id = i + 1;
    }
    sort(cowLocs, cowLocs + cowCount, byX);

    int minDist = INF;
    multiset<Coord> cows;
    int left = 0;
    pair<int, int> closest;
    for (int i = 0; i < cowCount; i++) {
        while (!cows.empty() && left < i && abs(cowLocs[left].x - cowLocs[i].x) > minDist) {
            cows.erase(cows.find(cowLocs[left]));
            left++;
        }
        auto lo = cows.lower_bound(Coord{-INF, cowLocs[i].y - minDist, cowLocs[i].id});
        auto hi = cows.upper_bound(Coord{INF, cowLocs[i].y + minDist, cowLocs[i].id});
        for (auto iter = lo; iter != hi; iter++) {
            if (cowLocs[i].calcDist(*iter) < minDist) {
                minDist = cowLocs[i].calcDist(*iter);
                closest.first = min(cowLocs[i].id, (*iter).id);
                closest.second = max(cowLocs[i].id, (*iter).id);
            } else if(cowLocs[i].calcDist(*iter) == minDist) {
                int bot = min(cowLocs[i].id, (*iter).id);
                int top = max(cowLocs[i].id, (*iter).id);
                if (bot < closest.first) {
                    closest.first = bot;
                    closest.second = top;
                } else if (bot == closest.first) closest.second = min(closest.second, top);
            }
        }
        cows.insert(cowLocs[i]);
    }
    cout << closest.first << " " << closest.second << endl;
    return 0;
}

