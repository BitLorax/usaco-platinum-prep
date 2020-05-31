//
// Created by WillJ on 7/4/2019.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>

#define INF 2000000000
#define MAX_BUILDINGCNT 40000

using namespace std;

struct ChangePt {
    long long x, height, mag;
    bool operator<(const ChangePt &a) const {
        return x < a.x;
    }
};

ChangePt changePts[MAX_BUILDINGCNT * 2];

int main() {
    int buildingCount; cin >> buildingCount;
    for (int i = 0; i < buildingCount; i++) {
        long long a, b, c; cin >> a >> b >> c;
        changePts[i] = ChangePt{a, c, 1};
        changePts[i + buildingCount] = ChangePt{b, c, -1};
    }
    sort(changePts, changePts + 2 * buildingCount);

    multiset<long long> heights;
    unsigned long long area = 0;
    long long prevX = changePts[0].x;
    for (int i = 0; i < 2 * buildingCount; i++) {
        long long x = changePts[i].x;
        if (heights.size() > 0) area += (x - prevX) * *heights.rbegin();
        while (changePts[i].x == x) {
            if (changePts[i].mag == 1) heights.insert(changePts[i].height);
            else heights.erase(heights.find(changePts[i].height));
            i++;
        }
        i--;

        prevX = x;
    }

    cout << area << endl;
    return 0;
}
