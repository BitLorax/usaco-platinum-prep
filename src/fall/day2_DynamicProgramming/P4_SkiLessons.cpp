//
// Created by WillJ on 9/17/2018.
//
#include <iostream>
#include <algorithm>

#define MAX_TIME 10000
#define MAX_CLASSCNT 100
#define MAX_SKILL 100

using namespace std;

struct SkiClass {
    int start, len, ability;
    bool operator<(const SkiClass &a) const {
        return start > a.start;
    }
};

SkiClass lessons[MAX_CLASSCNT + 1];
int slopes[MAX_SKILL + 1];
int DP[MAX_SKILL + 1][MAX_TIME + 1];

int main() {
    int time, classCount, slopeCount; cin >> time >> classCount >> slopeCount;
    for (int i = 0; i <= MAX_SKILL; i++) {
        slopes[i] = -1;
        for (int j = 0; j <= time; j++) {
            DP[i][j] = -1;
        }
    }
    for (int i = 0; i < classCount; i++) {
        cin >> lessons[i].start >> lessons[i].len >> lessons[i].ability;
    }
    for (int i = 0; i < slopeCount; i++) {
        int j, k; cin >> j >> k; //j is skillReq
        if (slopes[j] == -1 || k < slopes[j]) {
            slopes[j] = k;
        }
    }
    for (int i = 1; i <= MAX_SKILL; i++) {
        if (slopes[i - 1] != -1) {
            if (slopes[i] == -1) slopes[i] = slopes[i - 1];
            slopes[i] = min(slopes[i], slopes[i - 1]);
        }
    }
    sort(lessons, lessons + classCount);
    int currLesson = 0;
    int maxRuns = 0;
    DP[1][0] = 0;
    for (int i = 0; i <= time; i++) {
        for (int j = 1; j <= MAX_SKILL; j++) {
            if (DP[j][i] == -1) continue;
            maxRuns = max(maxRuns, DP[j][i]);
            //chill
            if (i != time) DP[j][i + 1] = max(DP[j][i + 1], DP[j][i]);
            //skill optimal slope
            if (slopes[j] != -1 && i + slopes[j] <= time) {
                DP[j][i + slopes[j]] = max(DP[j][i + slopes[j]], DP[j][i] + 1);
            }
        }
        //do classes
        while (currLesson < classCount && lessons[currLesson].start == i) {
            if (lessons[currLesson].len + i <= time) {
                for (int j = 1; j < lessons[currLesson].ability; j++) {
                    DP[lessons[currLesson].ability][lessons[currLesson].len + i] = max(DP[lessons[currLesson].ability][lessons[currLesson].len + i], DP[j][i]);
                }
            }
            currLesson++;
        }
    }
    cout << maxRuns << endl;
    return 0;
}


