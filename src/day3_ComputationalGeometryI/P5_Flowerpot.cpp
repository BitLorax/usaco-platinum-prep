//
// Created by WillJ on 9/27/2018.
//
#include <iostream>
#include <algorithm>
#include <set>

#define INF 2000000000
#define MAX_RAINDROPCNT 100000

using namespace std;

struct Coord {
    int x, y;
};

Coord dropLocs[MAX_RAINDROPCNT];
multiset<int> heights;

int main() {
    int raindropCount, timeDiff; cin >> raindropCount >> timeDiff;
    for (int i = 0; i < raindropCount; i++) {
        cin >> dropLocs[i].x >> dropLocs[i].y;
    }
    sort(dropLocs, dropLocs + raindropCount);
    int minWidth = INF;
    int right = 0;
    heights.insert(dropLocs[right].y);
    for (int left = 0; left < raindropCount; left++) {
        while (*heights.rbegin() - *heights.begin() < timeDiff) {
            right++;
            if (right == raindropCount) break;
            heights.insert(dropLocs[right].y);
        }
        if (right == raindropCount && *heights.rbegin() - *heights.begin() < timeDiff) break;
        heights.erase(heights.find(dropLocs[left].y));
        minWidth = min(minWidth, dropLocs[right].x - dropLocs[left].x);
    }
    cout << ((minWidth != INF) ? minWidth : -1) << endl;
    return 0;
}

