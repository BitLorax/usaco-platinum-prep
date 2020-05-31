//
// Created by WillJ on 7/17/2019.
//

#include <iostream>
#include <fstream>

#define INF 2000000000
#define MAX_COWCNT 20

using namespace std;

struct Cow {
    int h, w, s;
};

Cow cows[MAX_COWCNT + 1];
int DP[(1 << MAX_COWCNT) + 1];

int main() {
    int cowCount, height; cin >> cowCount >> height;
    for (int i = 0; i < cowCount; i++)
        cin >> cows[i].h >> cows[i].w >> cows[i].s;

    for (int i = 0; i < (1 << cowCount); i++)
        DP[i] = -1;

    int maxSafety = 0;
    DP[0] = 0;
    for (int i = 0; i < (1 << cowCount); i++) {
        int curH = 0;
        for (int j = 0; j < cowCount; j++)
            if ((i & (1 << j)) != 0) curH += cows[j].h;
        if (curH >= height) maxSafety = max(maxSafety, DP[i]);
        for (int j = 0; j < cowCount; j++) {
            if ((i & (1 << j)) == 0) {
                if (DP[i] - cows[j].w < 0 && i) continue;
                DP[i ^ (1 << j)] = max(DP[i ^ (1 << j)], min((i ? DP[i] - cows[j].w : INF), cows[j].s));
            }
        }
    }

    if (maxSafety > 0) cout << maxSafety << endl;
    else cout << "Mark is too tall" << endl;
    return 0;
}
