//
// Created by WillJ on 7/2/2019.
//

#include <iostream>
#include <fstream>

#define INF 2000000000
#define MAX_LIMIT 45000
#define MAX_BALECNT 500

using namespace std;

bool DP[MAX_LIMIT + 1];
int bales[MAX_BALECNT];

int main() {
    int limit, baleCount; cin >> limit >> baleCount;
    for (int i = 0; i < baleCount; i++) {
        cin >> bales[i];
    }

    DP[0] = true;

    for (int i = 0; i < baleCount; i++) {
        for (int j = limit - bales[i]; j >= 0; j--) {
            if (!DP[j]) continue;
            DP[j + bales[i]] = true;
        }
    }
    for (int i = limit; i >= 0; i--) {
        if (DP[i]) {
            cout << i << endl;
            break;
        }
    }
    return 0;
}
