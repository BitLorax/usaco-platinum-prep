//
// Created by WillJ on 10/14/2018.
//
#include <iostream>
#include <algorithm>

#define MAX_COWCNT 50000

using namespace std;

struct Point {
    int x, mag;
    bool operator< (const Point a) const {
        return x < a.x;
    }
};

Point changePoints[MAX_COWCNT * 2];

int main() {
    int cowCount; cin >> cowCount;
    for (int i = 0; i < cowCount; i++) {
        cin >> changePoints[i * 2].x >> changePoints[i * 2 + 1].x; changePoints[i * 2 + 1].x++;
        changePoints[i * 2].mag = 1; changePoints[i * 2 + 1].mag = -1;
    }
    sort(changePoints, changePoints + 2 * cowCount);
    int sum = 0;
    int maxSum = 0;
    for (int i = 0; i < cowCount * 2; i++) {
        sum += changePoints[i].mag;
        while (i + 1 < cowCount * 2 && changePoints[i].x == changePoints[i + 1].x) {
            sum += changePoints[++i].mag;
        }
        maxSum = max(maxSum, sum);
    }
    cout << maxSum << endl;
    return 0;
}

