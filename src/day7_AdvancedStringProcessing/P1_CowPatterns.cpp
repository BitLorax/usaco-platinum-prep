//
// Created by Will Liang on 10/21/2018.
//
#include <iostream>
#include <algorithm>
#include <vector>

#define MAX_COWCNT 100000
#define MAX_SPOTCNT 25

using namespace std;

int cows[MAX_COWCNT];
int pattern[MAX_COWCNT];
int KMP[MAX_COWCNT];
int map[MAX_SPOTCNT + 1]; //pattern val to cow index
vector<int> foundLocs;

bool confirm(int patVal, int indx, int map[], int vals[]) { //relative comparison
    if (map[patVal] != -1) return vals[map[patVal]] == vals[indx];
    for (int i = 1; i <= MAX_SPOTCNT; i++) {
        if (map[i] == -1) continue;
        if (i < patVal && vals[map[i]] >= vals[indx]) return false;
        if (i > patVal && vals[map[i]] <= vals[indx]) return false;
    }
    map[patVal] = indx;
    return true;
}

int main() {
    int cowCount, troubleCount, spotMax; cin >> cowCount >> troubleCount >> spotMax;
    for (int i = 0; i < cowCount; i++) cin >> cows[i];
    for (int i = 0; i < troubleCount; i++) cin >> pattern[i];

    for (int k = 0; k <= MAX_SPOTCNT; k++) map[k] = -1;

    //compute KMP array
    KMP[0] = -1; KMP[1] = 0;
    int i = 2, len = 0;
    while (i <= troubleCount) {
        if (confirm(pattern[len], i - 1, map, pattern)) { //pattern[i - 1] == pattern[len]
            KMP[i++] = ++len;
        } else if (len > 0) {
            len = KMP[len];
            for (int k = 1; k <= MAX_SPOTCNT; k++) {
                if (map[k] >= len) map[k] = -1;
            }
        }
        else KMP[i++] = 0;
    }

    for (int k = 0; k <= MAX_SPOTCNT; k++) map[k] = -1;

    int found = 0;
    //KMP algorithm
    int txtIndx = 0, patIndx = 0;
    while (txtIndx + patIndx < cowCount) {
        if (patIndx < troubleCount && confirm(pattern[patIndx], patIndx + txtIndx, map, cows)) {
            patIndx++;
            if (patIndx == troubleCount) {
                found++;
                foundLocs.push_back(txtIndx);
            }
        } else {
            txtIndx += patIndx - KMP[patIndx];
            for (int k = 1; k <= MAX_SPOTCNT; k++) {
                if (map[k] != -1) {
                    map[k] += patIndx - KMP[patIndx];
                }
                if (map[k] >= txtIndx + KMP[patIndx]) {
                    map[k] = -1;
                }
            }
            if (patIndx > 0) patIndx = KMP[patIndx];
        }
    }
    cout << found << endl;
    for (int i : foundLocs) cout << i + 1 << endl;
    return 0;
}