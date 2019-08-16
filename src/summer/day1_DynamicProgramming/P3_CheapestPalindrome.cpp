//
// Created by WillJ on 7/1/2019.
//

// subproblem: all costs are equal

// DP[i][j] is answer for substring i ... (j - 1)

#include <iostream>
#include <fstream>

#define INF 2000000000
#define MAX_LETTERCNT 26
#define MAX_LEN 2000

using namespace std;

string tag;
int costs[26]; // inserting on one end = deleting on other end; use cheapest option
int DP[MAX_LEN + 1][MAX_LEN + 1];

int solve(int lo, int hi) { //[lo, hi)
    if (lo > hi) return DP[lo][hi] = 0;
    if (DP[lo][hi] != 0) return DP[lo][hi];
    if (tag[lo] == tag[hi - 1]) return DP[lo][hi] = solve(lo + 1, hi - 1);
    else {
        return DP[lo][hi] = min(costs[tag[lo] - 'a'] + solve(lo + 1, hi), costs[tag[hi - 1] - 'a'] + solve(lo, hi - 1));
    }
}

int main() {
    int letterCount, len; cin >> letterCount >> len;
    cin >> tag;
    for (int i = 0; i < letterCount; i++) {
        char a; int b, c; cin >> a >> b >> c;
        costs[a - 'a'] = min(b, c);
    }

    cout << solve(0, len) << endl;
    return 0;
}