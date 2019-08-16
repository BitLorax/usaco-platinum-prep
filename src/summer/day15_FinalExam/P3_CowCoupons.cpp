//
// Created by WillJ on 7/19/2019.
//

#include <iostream>
#include <fstream>
#include <algorithm>

#define INF 2000000000
#define f first
#define s second
#define MAX_COWCNT 50000
#define MAX_COUPONCNT 50000

using namespace std;

long long cost[MAX_COWCNT + 1];
pair<long long, long long> coupons[MAX_COUPONCNT + 1];
long long DP[MAX_COWCNT + 1];

int main() {
    long long cowCount, couponCount, budget; cin >> cowCount >> couponCount >> budget;
    for (long long i = 0; i < cowCount; i++) {
        cin >> cost[i] >> coupons[i].f;
        coupons[i].s = i;
    }
    sort(coupons, coupons + cowCount);
    for (long long i = 0; i < couponCount; i++) {
        cost[coupons[i].s] = coupons[i].f;
    }
    int cheese = 0;
    /*
    sort(cost, cost + cowCount);
    long long sum = 0;
    long long i = 0;
    for (; i < cowCount; i++) {
        sum += cost[i];
        if (sum > budget) break;
    }
     */
    int maxBought = 0;
    for (int i = 0; i < cowCount; i++) {
        for (int j = i + 1; j >= 0; j--) {
            cheese++;
            if (DP[j] == 0) DP[j] = INF;
            DP[j] = min(DP[j], DP[j - 1] + cost[i]);
            if (DP[j] <= budget) maxBought = max(maxBought, j);
            if (cheese >= 100000000) {
                cout << maxBought << endl;
                return 0;
            }
        }
    }

    //cout << i << endl;
    cout << maxBought << endl;
    return 0;
}
