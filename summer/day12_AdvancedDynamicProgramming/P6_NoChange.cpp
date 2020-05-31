//
// Created by WillJ on 7/16/2019.
//

#include <iostream>
#include <fstream>
#include <algorithm>

#define INF 2000000000
#define MAX_COINCNT 16
#define MAX_BUYCNT 100000

using namespace std;

int coins[MAX_COINCNT + 1];
int buys[MAX_BUYCNT + 1];
int pSums[MAX_BUYCNT + 1];
int DP[(1 << MAX_COINCNT) + 1];

int main() {
    int coinCount, buyCount; cin >> coinCount >> buyCount;
    int coinSum = 0;
    for (int i = 0; i < coinCount; i++) {
        cin >> coins[i];
        coinSum += coins[i];
    }
    for (int i = 0; i < buyCount; i++) {
        cin >> buys[i];
        pSums[i + 1] = pSums[i] + buys[i];
    }
    for (int i = 0; i < (1 << coinCount); i++) {
        for (int j = 0; j < coinCount; j++) {
            if ((i & (1 << j)) == 0) { //pay with coin j for next purchases
                auto it = upper_bound(pSums, pSums + (buyCount + 1), pSums[DP[i]] + coins[j]);
                int take = (it - pSums) - 1;
                DP[(i ^ (1 << j))] = max(DP[(i ^ (1 << j))], take);
            }
        }
    };

    int maxSave = -1;
    for (int i = 0; i < (1 << coinCount); i++) {
        if (DP[i] == buyCount) {
            int used = 0;
            for (int j = 0; j < coinCount; j++) {
                if ((i & (1 << j)) != 0) used += coins[j];
            }
            maxSave = max(maxSave, coinSum - used);
        }
    }

    cout << maxSave << endl;
    return 0;
}
