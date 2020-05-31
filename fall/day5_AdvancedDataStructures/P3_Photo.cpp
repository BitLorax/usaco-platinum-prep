//
// Created by WillJ on 10/13/2018.
//
#include <iostream>

#define INF 2000000000
#define MAX_COWCNT 200000

using namespace std;

int DP[MAX_COWCNT + 1];
int closest[MAX_COWCNT + 1];
int farthest[MAX_COWCNT + 1];

int main() {
    int cowCount, photoCount; cin >> cowCount >> photoCount;
    for (int i = 0; i <= cowCount; i++) {
        closest[i] = INF; farthest[i] = -1;
    }
    for (int i = 0; i < photoCount; i++) {
        int a, b; cin >> a >> b; a--; b--;
        closest[b] = min(closest[b], a);
        farthest[b] = max(farthest[b], a);
    }
    for (int i = cowCount; i >= 0; i--) {
        if (closest[i] == INF) closest[i] = i;
        if (i != cowCount) closest[i] = min(closest[i], closest[i + 1]);
    }
    for (int i = 0; i < cowCount; i++) {
        farthest[i] = max(farthest[i], farthest[i - 1]);
    }
    DP[0] = 1;
    for (int i = 1; i <= cowCount; i++) {
        int lo = farthest[i - 1];
        int hi = closest[i];
        if (lo < hi) {
            for (int j = lo; j < hi; j++) {
                DP[i] = max(DP[i], DP[j] + 1);
            }
        } else {
            DP[i] = -1;
        }
        cout << i << " " << DP[i] << endl;
    }
    cout << DP[cowCount] - 1 << endl;
    return 0;
}
