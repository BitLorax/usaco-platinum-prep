//
// Created by WillJ on 7/3/2019.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#define INF 2000000000
#define MAX_COWCNT 500

using namespace std;

struct Cow {
    int x, y;
    bool isH;
    bool operator<(const Cow &a) const {
        if (x == a.x) return isH;
        return x < a.x;
    }
};

Cow cows[MAX_COWCNT + 1];
vector<int> hY;

int main() {
    int cowCount; cin >> cowCount;
    for (int i = 0; i < cowCount; i++) {
        cin >> cows[i].x >> cows[i].y;
        char a; cin >> a;
        cows[i].isH = (a == 'H');
        if (cows[i].isH) hY.push_back(cows[i].y);
    }
    sort(cows, cows + cowCount);
    sort(hY.begin(), hY.end());

    int maxH = 0, minSize = INF;
    for (int i = 0; i < hY.size(); i++) {
        for (int j = i + 1; j < hY.size(); j++) {
            int top = hY[j], bot = hY[i];
            int l = -1, r, h = 0;
            for (int k = 0; k < cowCount; k++) {
                r = cows[k].x;
                while (cows[k].x == r) {
                    k++;
                    if (cows[k - 1].y > top || cows[k - 1].y < bot) continue;
                    if (!cows[k - 1].isH) {
                        l = -1;
                        h = 0;
                    } else {
                        if (l == -1) l = cows[k - 1].x;
                        h++;
                    }
                }
                k--;
                if (h >= maxH) {
                    minSize = (h > maxH) ? (top - bot) * (r - l) : min(minSize, (top - bot) * (r - l));
                    maxH = h;
                }
            }
        }
    }

    cout << maxH << endl;
    cout << minSize << endl;
    return 0;
}
