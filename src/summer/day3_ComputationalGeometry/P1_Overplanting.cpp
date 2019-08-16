//
// Created by WillJ on 7/3/2019.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>

#define INF 2000000000
#define MAX_RECTCNT 1000

using namespace std;

struct vLine {
    int x, y1, y2, mag, id;
    bool operator<(const vLine &a) const {
        return x < a.x;
    }
};
struct hLine {
    int y, x1, x2, mag, id;
    bool operator<(const hLine &a) const {
        return y < a.y;
    }
};

hLine hSides[2 * MAX_RECTCNT];
vLine vSides[2 * MAX_RECTCNT];
int indxMag[MAX_RECTCNT * MAX_RECTCNT];
vector<int> recIndices[MAX_RECTCNT + 1];
int side[MAX_RECTCNT * MAX_RECTCNT];

int main() {
    int rectCount; cin >> rectCount;
    for (int i = 0; i < rectCount; i++) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        vSides[2 * i].x = a; vSides[2 * i + 1].x = c;
        vSides[2 * i].y1 = vSides[2 * i + 1].y1 = b;
        vSides[2 * i].y2 = vSides[2 * i + 1].y2 = d;
        vSides[2 * i].mag = 1; vSides[2 * i + 1].mag = -1;
        vSides[2 * i].id = vSides[2 * i + 1].id = i;

        hSides[2 * i].y = b; hSides[2 * i + 1].y = d;
        hSides[2 * i].x1 = hSides[2 * i + 1].x1 = a;
        hSides[2 * i].x2 = hSides[2 * i + 1].x2 = c;
        hSides[2 * i].mag = 1; hSides[2 * i + 1].mag = -1;
        hSides[2 * i].id = hSides[2 * i + 1].id = i;
    }
    sort(hSides, hSides + 2 * rectCount);
    sort(vSides, vSides + 2 * rectCount);

    set<int> curHSides;
    int indx = 0, prevY = hSides[2 * rectCount - 1].y;
    for (int i = 2 * rectCount - 1; i >= 0; i--) {
        int y = hSides[i].y;
        for (int j : curHSides) recIndices[j].push_back(indx);
        indxMag[indx] = prevY - y;
        indx++;
        while (i >= 0 && hSides[i].y == y) {
            if (hSides[i].mag == 1) curHSides.insert(hSides[i].id);
            else curHSides.erase(curHSides.find(hSides[i].id));
            i--;
        }
        i++;
        prevY = y;
    }

    long long area = 0;
    int prevX = vSides[0].x;
    for (int i = 0; i < 2 * rectCount; i++) {
        int x = vSides[i].x;
        long long sum = 0;
        for (int j = 0; j < indx; j++) {
            if (side[j] > 0) sum += indxMag[j];
        }
        area += (x - prevX) * sum;
        while (i < 2 * rectCount && vSides[i].x == x) {
            if (vSides[i].mag == 1) {
                for (int j : recIndices[vSides[i].id]) side[j]++;
            } else {
                for (int j : recIndices[vSides[i].id]) side[j]--;
            }
            i++;
        }
        i--;
        prevX = x;
    }

    cout << area << endl;
    return 0;
}
