//
// Created by WillJ on 10/13/2018.
//
#include <iostream>

#define INF 2000000000
#define MAX_COWCNT 200000

using namespace std;

int DP[MAX_COWCNT + 10];
int closest[MAX_COWCNT + 10];
int farthest[MAX_COWCNT + 10];

int main() {
    int cowCount, photoCount; cin >> cowCount >> photoCount;
    for (int i = 0; i <= cowCount; i++) closest[i] = cowCount + 2;
    for (int i = 0; i < photoCount; i++) {
        int a, b; cin >> a >> b;
        closest[a] = min(closest[a], b + 1); //[a, b)
        farthest[a] = max(farthest[a], b + 1);
    }
    closest[cowCount + 1] = cowCount + 2;
    for (int i = cowCount - 1; i >= 0; i--) closest[i] = min(closest[i], closest[i + 1]);
    for (int i = 1; i <= cowCount; i++) farthest[i] = max(farthest[i], farthest[i - 1]);
    DP[cowCount + 1] = 0;


    for (int i = cowCount; i >= 0; i--) {
        int lo = max(i + 1, farthest[i]);
        int hi = closest[i + 1];
        if (lo < hi) {
            DP[i] = -1;
            for (; lo < hi; lo++) {
                DP[i] = max(DP[i], (DP[lo] == -1) ? -1 : DP[lo] + 1);
            }
        } else {
            DP[i] = -1;
        }
    }
    cout << ((DP[0] == -1) ? DP[0] : DP[0] - 1) << endl;
    return 0;
}

