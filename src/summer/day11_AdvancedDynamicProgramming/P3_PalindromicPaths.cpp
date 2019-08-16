//
// Created by WillJ on 7/15/2019.
//

#include <iostream>
#include <fstream>

#define INF 2000000000
#define f first
#define s second
#define MAX_LEN 500
#define MOD 1000000007

using namespace std;

int len;
char arr[MAX_LEN + 1][MAX_LEN + 1];
long long DP[2][MAX_LEN + 1][MAX_LEN + 1];

int main() {
    cin >> len;
    for (int i = 0; i < len; i++) {
        string row; cin >> row;
        for (int j = 0; j < len; j++) {
            arr[j][i] = row[j];
        }
    }
    for (int i = 0; i < len; i++) {
        DP[(len - 1) % 2][i][i] = 1;
    }
    for (int l = len - 1; l > 0; l--) {
        for (int i = 0; i < len; i++)
            for (int j = 0; j < len; j++)
                DP[(l - 1) % 2][i][j] = 0;
        for (int i = 0; i <= l; i++) {
            for (int j = 0; j <= l; j++) {
                if (DP[l % 2][i][j] == 0) continue;
                pair<int, int> one = make_pair(i, l - i);
                pair<int, int> two = make_pair((len - 1) - (l - j), (len - 1) - j);
                if (one.f - 1 >= 0 && two.f + 1 < len && arr[one.f - 1][one.s] == arr[two.f + 1][two.s]) //left and right
                    DP[(l - 1) % 2][i - 1][j] = (DP[(l - 1) % 2][i - 1][j] + DP[l % 2][i][j]) % MOD;
                if (one.f - 1 >= 0 && two.s + 1 < len && arr[one.f - 1][one.s] == arr[two.f][two.s + 1]) //left and down
                    DP[(l - 1) % 2][i - 1][j - 1] = (DP[(l - 1) % 2][i - 1][j - 1] + DP[l % 2][i][j]) % MOD;
                if (one.s - 1 >= 0 && two.f + 1 < len && arr[one.f][one.s - 1] == arr[two.f + 1][two.s]) //up and right
                    DP[(l - 1) % 2][i][j] = (DP[(l - 1) % 2][i][j] + DP[l % 2][i][j]) % MOD;
                if (one.s - 1 >= 0 && two.s + 1 < len && arr[one.f][one.s - 1] == arr[two.f][two.s + 1]) //up and down
                    DP[(l - 1) % 2][i][j - 1] = (DP[(l - 1) % 2][i][j - 1] + DP[l % 2][i][j]) % MOD;
            }
        }
        for (int i = 0; i <= l; i++) {
            for (int j = 0; j <= l; j++) {
                DP[l % 2][i][j] = DP[(l - 1) % 2][i][j];
            }
        }
    }

    cout << DP[0][0][0] << endl;
    return 0;
}
