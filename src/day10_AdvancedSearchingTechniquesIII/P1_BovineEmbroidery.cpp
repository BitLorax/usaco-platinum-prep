//
// Created by WillJ on 11/11/2018.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>

#define MAX_THREADCNT 50000
#define PI atan(1) * 4

using namespace std;

vector<pair<long double, long double>> endpts;

bool compPts (const pair<long double, long double> &a, const pair<long double, long double> &b) {
    long double angA = asin(a.second);
    if (a.first < 0) angA = PI - angA;
    long double angB = asin(b.second);
    if (b.first < 0) angB = PI - angB;
    return angA < angB;
}

bool validDiscriminant(int a, int b, int c, int d) { return (4 * b * b * c * c - 4 * (a * a + b * b) * (c * c - a * a * d * d)) >= 0; }
pair<long double, long double> calcY(int a,int b, int c, int d) {
    long double one = (-(2 * b * c) + sqrt(4 * b * b * c * c - 4 * (a * a + b * b) * (c * c - a * a * d * d))) / (2 * (a * a + b * b));
    long double two = (-(2 * b * c) - sqrt(4 * b * b * c * c - 4 * (a * a + b * b) * (c * c - a * a * d * d))) / (2 * (a * a + b * b));
    return make_pair(one, two);
}

int main() {
    int threadCount, radius; cin >> threadCount >> radius;
    for (int i = 0; i < threadCount; i++) {
        int a, b, c; cin >> a >> b >> c;
        if (!validDiscriminant(a, b, c, radius)) continue;
        pair<long double, long double> y = calcY(a, b, c, radius); //MAKE CALC X IN CASE Y1 == Y2
        endpts.push_back(make_pair(radius * radius - y.first * y.first, y.first));
        endpts.push_back(make_pair(radius * radius - y.second * y.second, y.second));
    }
    sort(endpts.begin(), endpts.end(), compPts);
    for (pair<long double, long double> a : endpts) {
        cout << std::setprecision(3) << a.first << " " << std::setprecision(3) << a.second << endl;
    }
    return 0;
}

