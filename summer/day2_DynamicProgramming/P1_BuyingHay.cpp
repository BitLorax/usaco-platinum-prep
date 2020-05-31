//
// Created by WillJ on 7/2/2019.
//

#include <iostream>
#include <fstream>

#define INF 2000000000
#define MAX_SUPPLIERCNT 100
#define MAX_REQ 50000

using namespace std;

pair<int, int> suppliers[MAX_SUPPLIERCNT];
int DP[MAX_REQ + 1];

int main() {
    int supplierCount, req; cin >> supplierCount >> req;
    for (int i = 0; i < supplierCount; i++) {
        cin >> suppliers[i].first >> suppliers[i].second;
    }
    for (int i = 0; i <= req; i++) {
        DP[i] = INF;
    }
    DP[0] = 0;
    for (int i = 0; i < req; i++) {
        if (DP[i] == INF) continue;
        for (int j = 0; j < supplierCount; j++) {
            DP[min(i + suppliers[j].first, req)] = min(DP[min(i + suppliers[j].first, req)], DP[i] + suppliers[j].second);
        }
    }

    cout << DP[req] << endl;
    return 0;
}
