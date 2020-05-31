//
// Created by WillJ on 12/9/2018.
//

#include <iostream>

#define MAX 2000000000
#define MAX_COWCNT 10000
#define THRESHOLD 500

using namespace std;

pair<int, int> cowLocs[MAX_COWCNT];

int calcInconvenience(pair<int, int> cow, int x, int y) {
    return abs(x - cow.first) + abs(y - cow.second);
}

int main() {
    int cowCount; cin >> cowCount;
    int sumX = 0; int sumY = 0;
    for (int i = 0; i < cowCount; i++) {
        cin >> cowLocs[i].first >> cowLocs[i].second;
        sumX += cowLocs[i].first; sumY += cowLocs[i].second;
    }
    int minInconvenience = MAX;
    int counter = 0;
    for (int i = sumX / cowCount - THRESHOLD; i <= sumX / cowCount + THRESHOLD; i++) {
        for (int j = sumY / cowCount - THRESHOLD; j <= sumY / cowCount + THRESHOLD; j++) {
            int inconvenience = 0;
            bool onCow = false;
            for (int k = 0; k < cowCount; k++) {
                if (cowLocs[k].first == i && cowLocs[k].second == j) {
                    onCow = true;
                    break;
                }
                inconvenience += calcInconvenience(cowLocs[k], i, j);
            }
            if (onCow) continue;
            if (inconvenience < minInconvenience) {
                counter = 1;
                minInconvenience = inconvenience;
            } else if (inconvenience == minInconvenience) {
                counter++;
            }
        }
    }
    cout << minInconvenience << " " << counter << endl;
    return 0;
}

