//
// Created by WillJ on 7/15/2019.
//

#include <iostream>
#include <fstream>
#include <set>

#define INF 2000000000000000
#define MAX_COWCNT 100000

using namespace std;

long long cows[MAX_COWCNT + 1];
long long DP[MAX_COWCNT + 1];

int main() {
    long long cowCount, gap; cin >> cowCount >> gap;
    long long sum = 0;
    for (long long i = 0; i < cowCount; i++) {
        cin >> cows[i];
        sum += cows[i];
    }
    for (long long i = 0; i <= cowCount; i++) DP[i] = INF;

    multiset<long long> m;
    for (long long i = 0; i < cowCount; i++) {
        DP[i] = cows[i] + (m.size() > gap ? *m.begin() : 0);
        m.insert(DP[i]);
        if (i - gap - 1 >= 0) m.erase(m.find(DP[i - gap - 1]));
    }
    long long minVal = INF;
    for (long long i = cowCount - gap - 1; i < cowCount; i++) {
        minVal = min(minVal, DP[i]);
    }

    cout << sum - minVal << endl;
    return 0;
}
