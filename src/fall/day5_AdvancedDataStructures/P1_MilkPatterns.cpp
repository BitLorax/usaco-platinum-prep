//
// Created by WillJ on 10/8/2018.
//
#include <iostream>
#include <unordered_map>

#define MAX_DAYCNT 20000
#define PRIME 10000019

using namespace std;

int days[MAX_DAYCNT];
int dayCount, repeatCount;

struct Range {
    int *lo, *hi;
    size_t h;
};
struct hashRange {
    size_t operator() (const Range &a) const {
        return a.h;
    }
};
struct equalRange {
    bool operator() (const Range &a, const Range &b) const {
        return a.h == b.h && std::equal(a.lo, a.hi, b.lo); //equal() compares values in days
    }
};
bool test(int len) {
    unordered_map<Range, int, hashRange, equalRange> vals;
    Range curr{days, days + 1, 0};
    long long s = 1;
    for (int i = 0; i < len; i++) {
        curr.h = curr.h * PRIME + days[i];
        s *= PRIME;
    }
    for (int i = 0; i + len <= dayCount; i++) {
        if (++vals[curr] >= repeatCount) return true;
        curr.h = curr.h * PRIME - s * days[i] + days[i + len];
        curr.lo++; curr.hi++;
    }
    return false;
}

int main() {
    cin >> dayCount >> repeatCount;
    for (int i = 0; i < dayCount; i++) cin >> days[i];
    int lo = 0, hi = dayCount;

    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (test(mid)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << endl;
    return 0;
}

