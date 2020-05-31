//
// Created by WillJ on 7/16/2019.
//

#include <iostream>
#include <fstream>

#define INF 200000000000000
#define MAX_ROWCNT 700
#define MAX_REQ 20

using namespace std;

long long rowCount, req;
long long triangle[MAX_REQ + MAX_ROWCNT + 1][MAX_REQ + MAX_ROWCNT + 1];
long long lPreSum[MAX_ROWCNT + 1][MAX_ROWCNT + 1]; //start from left
long long rPreSum[MAX_ROWCNT + 1][MAX_ROWCNT + 1]; //start from right

long long getUpAvg(long long x, long long y, long long len) { //x and y is top of triangle
    long long sum = 0;
    for (long long j = 0; j < len; j++) {
        sum += lPreSum[x + j][y + j] - ((x > 0) ? lPreSum[x - 1][y + j] : 0);
    }
    long long ret = sum / (len * (len + 1) / 2);
    return sum / (len * (len + 1) / 2);
}
long long getDownAvg(long long x, long long y, long long len) { //x and y is bottom of triangle
    long long sum = 0;
    for (long long j = 0; j < len; j++) {
        sum += rPreSum[x - j][y - j] - ((x < (y - j)) ? rPreSum[x + 1][y - j] : 0);
    }
    long long ret = sum / (len * (len + 1) / 2);
    return sum / (len * (len + 1) / 2);
}


int main() {
    cin >> rowCount >> req;
    for (long long i = 0; i <= rowCount + req; i++) {
        for (long long j = 0; j <= rowCount + req; j++) {
            triangle[i][j] = INF;
        }
    }
    for (long long i = 0; i < rowCount; i++) {
        for (long long j = 0; j <= i; j++) {
            cin >> triangle[j][i];
        }
    }
    for (long long j = 0; j < rowCount; j++) {
        for (long long i = 0; i < rowCount; i++)
            lPreSum[i][j] = ((i > 0) ? lPreSum[i - 1][j] : 0) + triangle[i][j];
        for (long long i = j; i >= 0; i--)
            rPreSum[i][j] = ((i < j) ? rPreSum[i + 1][j] : 0) + triangle[i][j];
    }

    long long maxAvg = -INF;
    for (long long len = req; len < req * 2; len++) {
        for (long long j = 0; j + len <= rowCount; j++) {
            for (long long i = 0; i <= j; i++) {
                maxAvg = max(maxAvg, getUpAvg(i, j, len));
            }
        }
        for (long long j = len - 1; j < rowCount; j++) {
            for (long long i = len - 1; i <= (j - len + 1); i++) {
                maxAvg = max(maxAvg, getDownAvg(i, j, len));
            }
        }
    }

    cout << maxAvg << endl;
    return 0;
}
