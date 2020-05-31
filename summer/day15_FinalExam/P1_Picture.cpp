//
// Created by WillJ on 7/19/2019.
//

#include <iostream>
#include <fstream>
#include <algorithm>

#define INF 2000000000
#define MAX_RECTCNT 5000

using namespace std;

struct Side {
    int x, y1, y2, mag;
    bool operator<(const Side &a) const {
        return x < a.x;
    }
};

Side sides[MAX_RECTCNT * 2 + 1];
int side[20010];

int main() {
    int rectCount; cin >> rectCount;
    for (int i = 0; i < rectCount; i++) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        x1 += 10000; x2 += 10000; y1 += 10002; y2 += 10002;
        sides[i] = Side{x1, y1, y2, 1};
        sides[i + rectCount] = Side{x2, y1, y2, -1};
    }
    sort(sides, sides + 2 * rectCount);
    int prevX = sides[0].x;
    int perimeter = 0;
    for (int i = 0; i < 2 * rectCount; i++) {
        int curX = sides[i].x;
        int k = 0;
        for (int j = 0; j <= 20010; j++) {
            if (side[j] != 0) continue;
            if (j > 0 && side[j - 1] > 0) k++;
            if (j < 20000 && side[j + 1] > 0) k++;
        }
        perimeter += (curX - prevX) * k;
        while (sides[i].x == curX) {
            Side cur = sides[i++];
            for (int j = cur.y1; j < cur.y2; j++) {
                side[j] += cur.mag;
                if (side[j] == 1 && side[j] - cur.mag == 0) perimeter++;
                if (side[j] == 0 && side[j] - cur.mag == 1) perimeter++;
            }
        }
        i--;
        prevX = curX;
    }

    cout << perimeter << endl;
    return 0;
}
