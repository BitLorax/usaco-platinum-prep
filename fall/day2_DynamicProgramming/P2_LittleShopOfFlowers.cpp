//
// Created by WillJ on 9/16/2018.
//
#include <iostream>
#define INF 2000000000
#define MAX_FLOWERCNT 100
#define MAX_VASECNT 100

int DP[MAX_FLOWERCNT + 1][MAX_VASECNT + 1];

using namespace std;

int main() {
    int flowerCount, vaseCount; cin >> flowerCount >> vaseCount;
    for (int i = 1; i <= flowerCount; i++) {
        for (int j = 0; j <= vaseCount; j++) {
            DP[i][j] = -INF;
        }
    }
    int flowerInfo[MAX_FLOWERCNT + 1];
    for (int flowerNum = 1; flowerNum <= flowerCount; flowerNum++) {
        for (int j = 1; j <= vaseCount; j++) {
            cin >> flowerInfo[j];
        }
        for (int j = 1; j <= vaseCount; j++) {
            DP[flowerNum][j] = max(DP[flowerNum - 1][j - 1] + flowerInfo[j], DP[flowerNum][j - 1]);
        }
    }
    cout << DP[flowerCount][vaseCount] << endl;
    return 0;
}
