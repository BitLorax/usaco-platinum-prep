//
// Created by WillJ on 7/1/2019.
//

//DP[i][unclosed H]
//figure out unclosed G from total unclosed - H

#include <iostream>
#include <fstream>

#define INF 2000000000
#define MAX_COWLEN 1000
#define MOD 2012

using namespace std;

int DP[MAX_COWLEN + 1][MAX_COWLEN + 1];
int preSums[MAX_COWLEN + 1];

int main() {
    string cows; cin >> cows;
    int len = cows.length();
    int sum = 0;
    for (int i = 0; i < len; i++) {
        if (cows[i] == '(') sum++;
        else sum--;
        preSums[i] = sum;
    }

    DP[0][0] = 1; DP[0][1] = 1; //assume first cow is '(' because the cows must be balanced
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j <= len; j++) {
            if (DP[i][j] == 0) continue;
            if (cows[i + 1] == '(') {
                DP[i + 1][j + 1] = (DP[i + 1][j + 1] + DP[i][j]) % MOD;
                DP[i + 1][j] = (DP[i + 1][j] + DP[i][j]) % MOD;
            } else {
                if (j > 0) DP[i + 1][j - 1] = (DP[i + 1][j - 1] + DP[i][j]) % MOD;
                if (preSums[i] - j > 0) DP[i + 1][j] = (DP[i + 1][j] + DP[i][j]) % MOD;
            }
        }
    }

    cout << DP[len - 1][0] << endl;
    return 0;
}
