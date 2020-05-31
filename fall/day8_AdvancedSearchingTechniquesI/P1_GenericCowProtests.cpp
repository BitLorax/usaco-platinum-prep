//
// Created by WillJ on 10/28/2018.
//

#include <iostream>
#include <map>

#define MAX_COWCNT 100000
#define MOD 1000000009

using namespace std;

int cows[MAX_COWCNT];
long long prefxSums[MAX_COWCNT + 1];
long long fenwick[MAX_COWCNT + 1];
long long DP[MAX_COWCNT + 1];

long long queryFenwick(int index) {
    int ans = 0;
    for (; index > 0; index -= index&-index) {
        ans += fenwick[index];
        ans %= MOD;
    }
    return ans;
}
void updateFenwick(int index, long long add) {
    for (; index < MAX_COWCNT; index += index&-index) {
        fenwick[index] += add;
        fenwick[index] %= MOD;
    }
}

int main() {
    int cowCount; cin >> cowCount;
    int sum = 0;
    for (int i = 0; i < cowCount; i++) {
        cin >> cows[i];
        sum += cows[i];
        prefxSums[i + 1] = sum;
    }

    //coord compression
    map<int, int> toIndx;
    for (int i = 0; i <= cowCount; i++) {
        toIndx[prefxSums[i]] = 1;
    }
    int indx = 0;
    for (auto it = toIndx.begin(); it != toIndx.end(); it++) {
        it->second = ++indx; //don't use index 0 in BIT
    }

    DP[0] = 1;
    updateFenwick(toIndx[0], 1);
    for (int i = 1; i <= cowCount; i++) {
        int curIndx = toIndx[prefxSums[i]];
        DP[i] = queryFenwick(curIndx) % MOD;
        updateFenwick(curIndx, DP[i]);
    }

    cout << DP[cowCount] << endl;
    return 0;
}
