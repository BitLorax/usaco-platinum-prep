//
// Created by WillJ on 9/11/2018.
//
#include <iostream>
#define MAX_BITCNT 31

using namespace std;

long long choose[MAX_BITCNT + 1][MAX_BITCNT + 1];

int main() {
    long long bitCount, oneCount, number; cin >> bitCount >> oneCount >> number;
    for (int i = 0; i < bitCount; i++) {
        choose[0][i] = 1;
    }
    for (int i = 1; i < bitCount; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i) choose[i][j] = 1;
            else choose[i][j] = choose[i - 1][j] + choose[i - 1][j - 1];
        }
    }
    for (int i = 1; i < bitCount; i++) {
        for (int j = 1; j <= bitCount; j++) {
            choose[i][j] += choose[i][j - 1];
        }
    }
    while (true) {
        if (bitCount == 0) break;
        long long i = choose[bitCount - 1][oneCount];
        if (number > i) {
            cout << 1;
            number -= i;
            oneCount--;
        } else {
            cout << 0;
        }
        bitCount--;
    }
    return 0;
}

