//
// Created by WillJ on 7/4/2019.
//

//cosntruct suffix array but cyclic by doubling the string
//terminating character should be larger than characters to invalidate the invalid suffixs
//answer is first suffix after sort

#include <iostream>
#include <fstream>
#include <algorithm>

#define INF 2000000000
#define MAX_LEN 100000

using namespace std;

struct Suffix {
    long long indx; //starting indx
    pair<long long, long long> rank;
    bool operator<(const Suffix &a) const {
        if (rank.first == a.rank.first) return rank.second < a.rank.second;
        return rank.first < a.rank.first;
    }
};

long long len;
char str[2 * MAX_LEN + 1];
Suffix suffixes[2 * MAX_LEN + 1];
long long indx[2 * MAX_LEN + 1];

void construct() {
    len *= 2;
    str[len] = '~';
    for (int i = 0; i < len; i++) {
        suffixes[i] = Suffix{i, make_pair(str[i] - 'a', str[i + 1] - 'a')};
    }
    sort(suffixes, suffixes + len);
    for (int k = 2; k < len; k *= 2) {
        int rank = 0;
        Suffix pre = suffixes[0];
        for (int i = 0; i < len; i++) {
            if (suffixes[i].rank == pre.rank) {
                pre = suffixes[i];
                suffixes[i].rank.first = rank;
            } else {
                pre = suffixes[i];
                suffixes[i].rank.first = ++rank;
            }
            indx[suffixes[i].indx] = i;
        }
        for (int i = 0; i < len; i++) {
            suffixes[i].rank.second = ((suffixes[i].indx + k / 2 < len) ?
                                       suffixes[indx[suffixes[i].indx + k / 2]].rank.first : INF);
        }
        sort(suffixes, suffixes + len);
    }
}



int main() {
    cin >> len;
    for (long long i = 0; i < len; i++) {
        char a; cin >> a;
        str[i] = str[i + len] = a;
    }
    construct();
    long long minIndx = suffixes[0].indx;
    for (int i = 1; i < len; i++) {
        if (suffixes[i].rank.first != suffixes[i - 1].rank.first || suffixes[i].rank.second != suffixes[i - 1].rank.second) break;
        minIndx = min(minIndx, suffixes[i].indx);
    }
    cout << minIndx << endl;
    return 0;
}
