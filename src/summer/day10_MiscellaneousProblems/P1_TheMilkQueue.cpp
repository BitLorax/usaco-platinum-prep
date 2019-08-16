//
// Created by WillJ on 7/12/2019.
//

//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>

#define INF 2000000000
#define MAX_COWCNT 25000

using namespace std;

struct Cow {
    int a, b;
//    bool operator<(const Cow &u) const {
//        if (b >= a && u.b >= u.a) return a < u.a;
//        if (b < a && u.b < u.a) return b > u.b;
//        return b >= a;
//    }
};

bool comp(const Cow &u, const Cow &v) {
    if (u.b >= u.a && v.b >= v.a) return u.a < v.a;
    if (u.b < u.a && v.b < v.a) return u.b > v.b;
    return u.b >= u.a;
}

Cow cows[MAX_COWCNT + 1];

int main() {
    int cowCount; cin >> cowCount;
    for (int i = 0; i < cowCount; i++) {
        cin >> cows[i].a >> cows[i].b;
    }
    sort(cows, cows + cowCount, comp);

    int time = 0;
    queue<int> one; queue<int> two;

    for (int i = 0; i < cowCount; i++) {
        one.push(i);
    }

    int oneFree = 0, twoFree = cows[0].a;
    while (!one.empty() || !two.empty()) {
        int a = (one.empty() ? INF : one.front());
        int b = (two.empty() ? INF : two.front());
        if (!two.empty() && time >= twoFree) {
            twoFree += cows[b].b;
            two.pop();
        }
        if (!one.empty() && time >= oneFree) {
            oneFree += cows[a].a;
            two.push(a);
            one.pop();
        }
        if (two.size() == 1) twoFree = max(twoFree, oneFree);
        time = min((one.empty() ? INF : oneFree), twoFree);
    }

    cout << time << endl;
    return 0;
}
