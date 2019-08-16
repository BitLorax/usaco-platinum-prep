#include <iostream>

#define MAX_TIMELEN 10000
#define MAX_EXHAUSTLIM 500

using namespace std;

int dists[MAX_TIMELEN + 1];
int DP[MAX_TIMELEN + 1][MAX_EXHAUSTLIM + 1];

int main() {
    int timeLen, exhaustLim; cin >> timeLen >> exhaustLim;
    for (int i= 0; i < timeLen; i++) {
        cin >> dists[i];
    }
    for (int i = 0; i <= timeLen; i++) {
        for (int j = 0; j <= exhaustLim; j++) {
            DP[i][j] = -1;
        }
    }
    DP[0][0] = 0;
    for (int i = 0; i < timeLen; i++) {
        for (int j = 0; j <= exhaustLim; j++) {
            if (DP[i][j] == -1) continue;
            if (j < exhaustLim) DP[i + 1][j + 1] = max(DP[i + 1][j + 1], DP[i][j] + dists[i]);
            if (i + j <= timeLen) DP[i + j][0] = max(DP[i + j][0], DP[i][j]);
            if (j == 0) DP[i + 1][0] = max(DP[i + 1][0], DP[i][j]);
        }
    }
    cout << DP[timeLen][0] << endl;
    return 0;
}