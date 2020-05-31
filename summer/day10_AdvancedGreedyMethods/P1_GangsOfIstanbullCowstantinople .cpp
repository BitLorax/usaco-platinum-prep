//
// Created by WillJ on 7/12/2019.
//

//majority algorithm

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define INF 2000000000
#define MAX_GANGCNT 100

using namespace std;

int cowCount, gangCount;
int gangs[MAX_GANGCNT + 1];

void update(int &curGang, int &curSize, int challengerGang) {
    if (curSize == 0) curGang = challengerGang;
    if (curGang == challengerGang) curSize++;
    else curSize--;
}

int simulate(int curGang, int curSize) {
    vector<int> curGangs;
    int curCowCount = 0;
    for (int i = 0; i < gangCount; i++) {
        curGangs.push_back(gangs[i]);
        curCowCount += gangs[i];
    }
    curCowCount -= gangs[0];

    while (curCowCount > 0) {
        int biggestGang = 1;
        for (int i = 1; i < curGangs.size(); i++) {
            if (curGangs[i] > curGangs[biggestGang]) biggestGang = i;
        }

        if (curGangs[biggestGang] > 0) {
            curGangs[biggestGang]--;
            update(curGang, curSize, biggestGang);
        }
        curCowCount--;
    }
    return curGangs[0] + ((curGang == 0) ? curSize : -curSize);
}

int main() {
    cin >> cowCount >> gangCount;
    for (int i = 0; i < gangCount; i++) {
        cin >> gangs[i];
    }

    int curGang = 0, curSize = 0;
    int bestResult = simulate(curGang, curSize);
    if (bestResult <= 0) cout << "NO";
    else {
        cout << "YES" << endl;
        cout << bestResult << endl;
        for (int i = 0; i < cowCount; i++) {
            int pCurGang = curGang, pCurSize = curSize;
            for (int j = 0; j < gangCount; j++) {
                if (gangs[j] == 0) continue;

                gangs[j]--;
                update(curGang, curSize, j);
                int result = simulate(curGang, curSize);
                if (result != bestResult) {
                    curGang = pCurGang;
                    curSize = pCurSize;
                    gangs[j]++;
                } else {
                    cout << (j + 1) << endl;
                    break;
                }
            }
        }
    }
    return 0;
}
