//
// Created by WillJ on 11/11/2018.
//

#include <iostream>

#define MAX_COINCNT 2000

using namespace std;

int DP[MAX_COINCNT + 1][MAX_COINCNT + 1]; //DP[coinsLeft][coinsTaken]
int prefixSums[MAX_COINCNT + 1];
int coins[MAX_COINCNT + 1];
int DPMax[MAX_COINCNT + 1][MAX_COINCNT + 1];

int main() {
    int coinCount; cin >> coinCount;
    int sum = 0, indx = 0;
    for (int i = 0; i < coinCount; i++) {
        cin >> coins[i];
        sum += coins[i];
    }
    for (int i = coinCount; i > 0; i--) {
        prefixSums[i] = sum;
        sum -= coins[indx++];
    }
    for (int i = 1; i <= coinCount; i++) {
        for (int j = 1; j <= i; j++) {
            DP[i][j] = prefixSums[i] - DPMax[i - j][min(i - j, 2 * j)];
            DPMax[i][j] = max(DPMax[i][j - 1], DP[i][j]);
        }
    }
    cout << max(DP[coinCount][1], DP[coinCount][2]) << endl;
    return 0;
}

