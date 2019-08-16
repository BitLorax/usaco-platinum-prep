//
// Created by WillJ on 9/21/2018.
//
#include <iostream>
#define MAX_CONSOLECNT 50
#define MAX_BUDGET 100000
#define MAX_GAMEPERCONSOLE 10

using namespace std;

long long maxProduction[MAX_BUDGET + 1];
long long maxAllProduction[MAX_BUDGET + 1];

int main() {
    int consoleCount, budget; cin >> consoleCount >> budget;
    for (int i = 0; i < consoleCount; i++) {
        int consolePrice, gameCount; cin >> consolePrice >> gameCount;
        for (int j = consolePrice; j <= budget; j++) {
            maxProduction[j] = maxAllProduction[j - consolePrice]; //buy only the console
        }
        for (int j = 0; j < gameCount; j++) {
            int price, val; cin >> price >> val;
            for (int k = budget - price; k >= consolePrice; k--) {
                maxProduction[k + price] = max(maxProduction[k + price], maxProduction[k] + val);
            }
        }
        for (int j = consolePrice; j <= budget; j++) {
            maxAllProduction[j] = max(maxAllProduction[j], maxProduction[j]);
        }
    }
    cout << maxAllProduction[budget] << endl;
    return 0;
}

