//
// Created by WillJ on 12/9/2018.
//

#include <iostream>
#include <algorithm>

#define MAX_BARNCNT 25000

using namespace std;

struct Corner {
    int x, y, id;
    Corner() {}
    Corner(int a, int b, int c) {
        x = a; y = b; id = c;
    }
};

bool compX(const Corner &a, const Corner &b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}
bool compY(const Corner &a, const Corner &b) {
    if (a.y == b.y) return a.x < b.x;
    return a.y < b.y;
}

int coords[MAX_BARNCNT][4];
bool failed[MAX_BARNCNT];
Corner corners[MAX_BARNCNT * 4];

int main() {
    int barnCount; cin >> barnCount;
    for (int i = 0; i < barnCount; i++) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        coords[i][0] = x1; coords[i][1] = y1; coords[i][2] = x2; coords[i][3] = y2;
        corners[i * 4] = Corner(x1, y1, i);
        corners[i * 4 + 1] = Corner(x1, y2, i);
        corners[i * 4 + 2] = Corner(x2, y1, i);
        corners[i * 4 + 3] = Corner(x2, y2, i);
    }
    sort(corners, corners + 4 * barnCount, compX);
    for (int i = 0; i < barnCount; i++) {
        for (int j = 0; j <= 2; j+= 2) {
            Corner *a = lower_bound(corners, corners + 4 * barnCount, Corner(coords[i][j], coords[i][1], 0), compX);
            Corner *b = lower_bound(corners, corners + 4 * barnCount, Corner(coords[i][j], coords[i][3], 0), compX);
            for (Corner *k = a; k < b; k++) {
                if (k->id != i) {
                    failed[k->id] = true;
                    failed[i] = true;
                }
            }
        }
    }
    sort(corners, corners + 4 * barnCount, compY);
    for (int i = 0; i < barnCount; i++) {
        for (int j = 1; j <= 3; j+= 2) {
            Corner *a = lower_bound(corners, corners + 4 * barnCount, Corner(coords[i][0], coords[i][j], 0), compY);
            Corner *b = lower_bound(corners, corners + 4 * barnCount, Corner(coords[i][2], coords[i][j], 0), compY);
            for (Corner *k = a; k < b; k++) {
                if (k->id != i) {
                    failed[k->id] = true;
                    failed[i] = true;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < barnCount; i++) {
        if (!failed[i]) ans++;
    }
    cout << ans << endl;
    return 0;
}

