//
// Created by WillJ on 9/10/2018.
//
#include <iostream>
#define MAX_DIVISION 1000

using namespace std;

bool DP[2][MAX_DIVISION + 110][MAX_DIVISION + 110];

int main() {
    int baleCount; cin >> baleCount;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j <= MAX_DIVISION; j++) {
            for (int k = 0; k <= MAX_DIVISION; k++) {
                DP[i][j][k] = false;
            }
        }
    }
    DP[0][0][0] = true;
    int total = 0;
    for (int i = 1; i <= baleCount; i++) {
        int bale; cin >> bale;
        total += bale;
        for (int j = 0; j < MAX_DIVISION; j++) {
            for (int k = 0; k < MAX_DIVISION; k++) {
                if (DP[(i + 1) % 2][j][k]) {
                    DP[i % 2][j][k] = true;
                    DP[i % 2][j + bale][k] = true;
                    DP[i % 2][j][k + bale] = true;
                }
            }
        }
    }
    int ans = MAX_DIVISION;
    for (int i = 0; i < MAX_DIVISION; i++) {
        for (int j = 0; j < MAX_DIVISION; j++) {
            if (DP[baleCount % 2][i][j]) {
                ans = min(ans, max(total - j - i, max(i, j)));
            }
        }
    }
    cout << ans << endl;
    return 0;
}

