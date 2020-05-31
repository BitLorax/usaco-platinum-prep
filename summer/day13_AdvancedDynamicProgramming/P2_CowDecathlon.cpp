//
// Created by WillJ on 7/17/2019.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define INF 2000000000
#define MAX_COWCNT 20
#define MAX_BONUSCNT 20

using namespace std;

struct Bonus {
    int req, add;
    bool operator<(const Bonus &a) const {
        return req < a.req;
    }
};

int DP[(1 << MAX_COWCNT) + 1];
vector<Bonus> bonus[MAX_BONUSCNT + 1];
int cows[MAX_COWCNT + 1][MAX_COWCNT + 1]; //[cow][event]

int main() {
    int cowCount, bonusCount; cin >> cowCount >> bonusCount;
    for (int i = 0; i < bonusCount; i++) {
        int a, b, c; cin >> a >> b >> c;
        bonus[a - 1].push_back(Bonus{b, c});
    }
    for (int i = 0; i < cowCount; i++)
        sort(bonus[i].begin(), bonus[i].end());

    for (int i = 0; i < cowCount; i++)
        for (int j = 0; j < cowCount; j++)
            cin >> cows[i][j];

    for (int i = 0; i < (1 << cowCount); i++) {
        int event = 0;
        for (int j = 0; j < cowCount; j++)
            if ((i & (1 << j)) != 0) event++;
        for (int j = 0; j < cowCount; j++) {
            if ((i & (1 << j)) == 0) {
                int sum = DP[i] + cows[j][event];
                for (Bonus k : bonus[event])
                    if (sum >= k.req) sum += k.add;
                DP[i ^ (1 << j)] = max(DP[i ^ (1 << j)], sum);
            }
        }
    }

    cout << DP[(1 << cowCount) - 1] << endl;
    return 0;
}
