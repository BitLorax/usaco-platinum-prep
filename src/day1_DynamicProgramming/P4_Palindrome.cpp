//
// Created by WillJ on 9/11/2018.
//
#include <iostream>
#define MAX_STRLEN 5000

using namespace std;

int DP[2][MAX_STRLEN + 10];

int main() {
    int strLen; cin >> strLen;
    char strOne[MAX_STRLEN + 10]; cin >> strOne;
    char strTwo[MAX_STRLEN + 10];
    for (int i = 0; i < strLen; i++) {
        strTwo[strLen - 1 - i] = strOne[i];
    }
    for (int i = 0; i <= strLen; i++) {
        for (int j = 0; j <= strLen; j++) {
            if (i == 0 || j == 0) {
                DP[i % 2][j] = 0;
                continue;
            }
            if (strOne[i - 1] == strTwo[j - 1]) DP[i % 2][j] = DP[(i + 1) % 2][j - 1] + 1;
            else DP[i % 2][j] = max(DP[(i + 1) % 2][j], DP[i % 2][j - 1]);
        }
    }
    cout << strLen - DP[strLen % 2][strLen] << endl;
    return 0;
}

