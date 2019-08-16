//
// Created by WillJ on 7/11/2019.
//

#include <iostream>
#include <fstream>

#define INF 2000000000
#define MAX_OPTIONCNT 50
#define MAX_CANDYCNT 40000

using namespace std;

int options[MAX_OPTIONCNT + 1];
pair<bool, int> fav[MAX_CANDYCNT + 1];
int DP[MAX_CANDYCNT + 1];


int main() {
    int candyCount, optionCount, favCount, increase; cin >> candyCount >> optionCount >> favCount >> increase;
    for (int i = 0; i < optionCount; i++) {
        cin >> options[i];
    }
    for (int i = 0; i < favCount; i++) {
        int a; cin >> a;
        fav[a].first = true;
    }
    for (int i = 0; i <= candyCount; i++) DP[i] = -1;
    DP[candyCount] = 0;
    bool s = true;
    for (int i = candyCount; i >= 0; i--) {
        if (DP[i] == -1) continue;
        if (fav[i].first && !s) {
            if (DP[i + increase] < DP[i]) { //no need to jump otherwise
                if (fav[i].second > favCount) {
                    cout << -1 << endl;
                    return 0;
                }
                fav[i].second++;
                DP[i + increase] = DP[i];
                i += increase + 1;
            }
            continue;
        }
        for (int j = 0; j < optionCount; j++) {
            if (i - options[j] >= 0) DP[i - options[j]] = max(DP[i - options[j]], DP[i] + options[j]);
        }
        s = false;
    }

    int maxCandy = 0;
    for (int i = 0; i <= candyCount; i++) maxCandy = max(maxCandy, DP[i]);
    cout << maxCandy << endl;
    return 0;
}
