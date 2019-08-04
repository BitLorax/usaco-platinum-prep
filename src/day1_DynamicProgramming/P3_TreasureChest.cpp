//
// Created by Will Liang on 9/9/2018.
//

#include <iostream>

#define INF 2000000000
#define MAX_COINCNT 5000

using namespace std;

int DP[MAX_COINCNT + 10][2];
int coins[MAX_COINCNT + 10];
int pSums[MAX_COINCNT + 10];

int main() {
    int coinCount; cin >> coinCount;
    int sum = 0;
    for (int i = 0; i < coinCount; i++) {
        cin >> coins[i];
        DP[i][1] = coins[i];
        pSums[i] = sum;
        sum += coins[i];
    }
    pSums[coinCount] = sum;
    for (int i = 2; i <= coinCount; i++) {
        for (int j = 0; j + i <= coinCount; j++) {
            int currSum = pSums[j + i] - pSums[j];
            DP[j][i % 2] = currSum - min(DP[j][(i + 1) % 2], DP[j + 1][(i + 1) % 2]);
        }
    }
    cout << DP[0][coinCount % 2] << endl;
    return 0;
}
/*
dp[len%2][startpos] = most coin you can earn if played optimally and its your turn, given coin range(start, start+ len - 1);
#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 5100

int n;
int coins[MAXN];
int pre[MAXN];
int dp[2][MAXN]; // length + startposition

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> coins[i];
    for (int i = 0; i < n; i++)
        pre[i + 1] = pre[i] + coins[i];
    for (int len = 1; len <= n; len++) // loop through length = 1 to n
        for (int start = 0; start + len <= n; start++)  // coins 0 -> n-1 // picked left coin or right coin
            dp[len % 2][start] = pre[start + len] - pre[start] + max(-dp[(len + 1) % 2][start + 1], -dp[(len + 1) % 2][start]);
    cout << dp[n%2][0];
}
 */


