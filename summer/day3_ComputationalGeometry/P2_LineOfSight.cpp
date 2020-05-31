//
// Created by WillJ on 7/3/2019.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

#define INF 2000000000
#define MAX_COWCNT 50000
#define PI 3.14159265358979323846

using namespace std;

struct ChangePt {
    long double pos;
    int mag;
    bool operator<(const ChangePt &a) const {
        return pos < a.pos;
    }
};

ChangePt changePts[2 * MAX_COWCNT + 100];

int main() {
    int cowCount, radius; cin >> cowCount >> radius;
    long long sum = 0, answer = 0;
    for (int i = 0; i < cowCount; i++) {
        long long x, y; cin >> x >> y;
        long double theta = atan2(y, x);
        long double gamma = acos(radius / sqrt(x * x + y * y));
        changePts[2 * i] = ChangePt{theta - gamma, 1};
        changePts[2 * i + 1] = ChangePt{theta + gamma, -1};

        if (changePts[2 * i].pos > 2 * PI) changePts[2 * i].pos -= 2 * PI;
        if (changePts[2 * i].pos < 0) changePts[2 * i].pos += 2 * PI;
        if (changePts[2 * i + 1].pos > 2 * PI) changePts[2 * i + 1].pos -= 2 * PI;
        if (changePts[2 * i + 1].pos < 0) changePts[2 * i + 1].pos += 2 * PI;

        if (changePts[2 * i].pos > changePts[2 * i + 1].pos) sum++;
    }
    sort(changePts, changePts + 2 * cowCount);

    for (int i = 0; i < 2 * cowCount; i++) {
        if (changePts[i].mag == 1) {
            answer += sum;
            sum++;
        } else {
            sum--;
        }
    }

    cout << answer << endl;
    return 0;
}
