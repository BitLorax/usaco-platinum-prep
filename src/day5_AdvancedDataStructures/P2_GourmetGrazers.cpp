//
// Created by WillJ on 10/8/2018.
//
#include <iostream>
#include <algorithm>
#include <set>

#define MAX_COWCNT 100000
#define MAX_GRASSCNT 100000

using namespace std;

struct Grass {
    int price, greenness;
    bool operator<(const Grass &a) const {
        return greenness < a.greenness;
    }
};

Grass grasses[MAX_GRASSCNT];
Grass demands[MAX_COWCNT];

int main() {
    int cowCount, grassCount; cin >> cowCount >> grassCount;
    for (int i = 0; i < cowCount; i++) {
        cin >> demands[i].price >> demands[i].greenness;
    }
    for (int i = 0; i < grassCount; i++) {
        cin >> grasses[i].price >> grasses[i].greenness;
    }
    sort(grasses, grasses + grassCount);
    sort(demands, demands + cowCount);

    multiset<int> prices;
    int currGrass = grassCount - 1;
    long long totalPrice = 0;
    for (int i = cowCount - 1; i >= 0; i--) {
        Grass demand = demands[i];
        while (currGrass >= 0 && grasses[currGrass].greenness >= demand.greenness) {
            prices.insert(grasses[currGrass].price);
            currGrass--;
        }
        totalPrice += *prices.lower_bound(demand.price);
        prices.erase(prices.lower_bound(demand.price));
    }
    cout << totalPrice << endl;
    return 0;
}

