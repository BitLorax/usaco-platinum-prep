//
// Created by WillJ on 7/15/2019.
//

#include <iostream>
#include <fstream>
#include <deque>

#define INF 2000000000
#define f first
#define s second
#define MAX_COINCNT 100
#define MAX_PAY 10000

using namespace std;

int val[MAX_COINCNT + 1];
int cap[MAX_COINCNT + 1];
int DP[2 * MAX_PAY + 1];
int tDP[2 * MAX_PAY + 1];
int kDP[2 * MAX_PAY + 1];

int main() {
    int coinCount, pay; cin >> coinCount >> pay;
    for (int i = 0; i < coinCount; i++) {
        cin >> val[i];
    }
    for (int i = 0; i < coinCount; i++) {
        cin >> cap[i];
    }
    for (int i = 0; i <= 2 * pay; i++) DP[i] = INF;
    DP[0] = 0;

    for (int c = 0; c < coinCount; c++) {
        for (int mod = 0; mod < val[c]; mod++) {
            for (int i = 0; i * val[c] + mod <= 2 * pay; i++) {
                tDP[i] = DP[i * val[c] + mod];
            }
            deque<pair<int, int>> dq;
            for (int i = 0; i * val[c] + mod <= 2 * pay; i++) {
                int f = tDP[i] - i;
                int s = i + cap[c];

                while (!dq.empty() && dq.back().f > f) dq.pop_back();
                dq.emplace_back(f, s);
                while (!dq.empty() && dq.front().s < i) dq.pop_front();

                if (!dq.empty()) tDP[i] = dq.front().f + i;
                else tDP[i] = INF;
            }
            for (int i = 0; i * val[c] + mod <= 2 * pay; i++) {
                DP[i * val[c] + mod] = min(DP[i * val[c] + mod], tDP[i]);
            }
        }
    }

    for (int i = 0; i <= 2 * pay; i++) kDP[i] = INF;
    kDP[0] = 0;
    for (int c = 0; c < coinCount; c++) {
        for (int i = 0; i + val[c] <= 2 * pay; i++) {
            kDP[i + val[c]] = min(kDP[i + val[c]], kDP[i] + 1);
        }
    }

    int minUsed = INF;
    for (int i = pay; i <= 2 * pay; i++) {
        if (DP[i] != INF && kDP[i - pay] != INF) {
            minUsed = min(minUsed, DP[i] + kDP[i - pay]);
        }
    }
    cout << ((minUsed == INF) ? -1 : minUsed) << endl;
    return 0;
}
