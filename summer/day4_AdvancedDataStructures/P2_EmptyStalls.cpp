//
// Created by WillJ on 7/4/2019.
//

#include <iostream>
#include <fstream>

#define INF 2000000000
#define MAX_STALLCNT 3000000

using namespace std;

long long fav[MAX_STALLCNT + 1];
bool occupied[MAX_STALLCNT + 1];

int main() {
    int stallCount, inputSize; cin >> stallCount >> inputSize;
    for (int i = 0; i < inputSize; i++) {
        long long x, y, a, b; cin >> x >> y >> a >> b;
        for (int j = 1; j <= y; j++) {
            fav[(a * j + b) % stallCount] += x;
        }
    }
    long long stall = 0, curCows = 0, cowsLeft = 0;
    for (int i = 0; i < stallCount; i++) cowsLeft += fav[i];
    while (cowsLeft > 0) {
        if (fav[stall] > 0) {
            curCows += fav[stall];
            fav[stall] = 0;
        }
        if (curCows > 0) {
            if (!occupied[stall]) {
                curCows--;
                cowsLeft--;
                occupied[stall] = true;
            }
        }
        stall++; stall %= stallCount;
    }

    for (int i = 0; i < stallCount; i++) {
        if (!occupied[i]) {
            cout << i << endl;
            break;
        }
    }
    return 0;
}
