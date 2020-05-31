//
// Created by WillJ on 7/12/2019.
//

#include <iostream>
#include <fstream>
#include <set>

#define INF 2000000000

using namespace std;

multiset<long long> planks;

int main() {
    long long plankCount; cin >> plankCount;
    for (long long i = 0; i < plankCount; i++) {
        long long a; cin >> a;
        planks.insert(a);
    }
    long long cost = 0;
    while (planks.size() > 1) {
        long long a = *planks.begin(); planks.erase(planks.begin());
        long long b = *planks.begin(); planks.erase(planks.begin());
        cost += a + b;
        planks.insert(a + b);
    }

    cout << cost << endl;
    return 0;
}
