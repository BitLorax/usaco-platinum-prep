//
// Created by WillJ on 12/2/2018.
//

#include <iostream>
#include <algorithm>
#include <set>

#define MAX_PLANKCNT 20000

using namespace std;

multiset<long long> plankLens;

int main() {
    int plankCount; cin >> plankCount;
    long long sum = 0;
    for (int i = 0; i < plankCount; i++) {
        int a; cin >> a;
        plankLens.insert(a);
        sum += a;
    }
    long long cutSum = 0;
    while (plankLens.size() > 1) {
        long long a = 0;
        a += *plankLens.begin();
        plankLens.erase(plankLens.begin());
        a += *plankLens.begin();
        plankLens.erase(plankLens.begin());
        plankLens.insert(a);
        cutSum += a;
    }
    cout << cutSum << endl;
    return 0;
}