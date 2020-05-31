//
// Created by WillJ on 7/2/2019.
//

#include <iostream>
#include <fstream>
#include <vector>

#define INF 2000000000

using namespace std;

int target;
bool success = false;

void dfs(int chain[], int size, int lim) {
    if (success) return;
    if (size > 0 && chain[size - 1] == target) success = true;
    if (size >= lim) return;

    if ((1 << (lim - size)) * chain[size - 1] < target) return;

    for (int i = 0; i < size; i++) {
        chain[size] = chain[i] + chain[size - 1];
        if ((1 << (lim - (size + 1))) * chain[size] < target) continue;
        dfs(chain, size + 1, lim);
        chain[size] = 0;
    }
}

int main() {
    cin >> target;
    int lim = 1;
    while (1) {
        int chain[20]; chain[0] = 1;
        dfs(chain, 1, lim);
        if (success) break;
        lim++;
    }

    cout << lim << endl;
    return 0;
}
