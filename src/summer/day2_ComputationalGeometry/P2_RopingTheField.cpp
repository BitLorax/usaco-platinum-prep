//
// Created by WillJ on 7/2/2019.
//

#include <iostream>
#include <fstream>
#include <cmath>

#define INF 2000000000
#define MAX_CORNERCNT 150
#define MAX_CIRCLECNT 100

using namespace std;

struct Coord {
    double x, y;
};

int cornerCount, circleCount, radius;
bool connected[MAX_CORNERCNT + 1][MAX_CORNERCNT + 1];
Coord corners[MAX_CORNERCNT + 1];
Coord circles[MAX_CIRCLECNT + 1];
int DP[MAX_CORNERCNT + 1][MAX_CORNERCNT + 1];

inline double getDist(Coord a, Coord b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
double getDist(Coord pt, Coord a, Coord b) {
    double ab = getDist(a, b);
    double ap = getDist(a, pt);
    double bp = getDist(b, pt);
    if (ab + bp <= ap || ab + ap <= bp) return sqrt(min(ap, bp));

    long long i = a.y - b.y;
    long long j = b.x - a.x;
    long long k = i * a.x + j * a.y;
    return abs(double(i * pt.x + j * pt.y - k) / sqrt(i * i + j * j));

}
int calcDP(int i, int j) {
    if (abs(i - j) == 1 || abs(i - j) == cornerCount) return 0;
    if (DP[i][j] != 0) return DP[i][j];
    for (int k = i + 1; k < j; k++) {
        DP[i][j] = connected[i][j] + max(calcDP(i + 1, j), calcDP(i, k) + calcDP(k, j));
    }
    return DP[i][j];
}

int main() {
    cin >> cornerCount >> circleCount >> radius;
    for (int i = 0; i < cornerCount; i++) {
        cin >> corners[i].x >> corners[i].y;
    }
    for (int i = 0; i < circleCount; i++) {
        cin >> circles[i].x >> circles[i].y;
    }
    for (int i = 0; i < cornerCount; i++) {
        for (int j = i + 2; j < cornerCount; j++) {
            if (i == 0 && j == cornerCount - 1) continue;
            connected[i][j] = true;
            for (int k = 0; k < circleCount; k++) {
                double dist = getDist(circles[k], corners[i], corners[j]);
                if (dist <= radius) {
                    connected[i][j] = false;
                    break;
                }
            }
            connected[j][i] = connected[i][j];
        }
    }

    for (int d = 2; d < cornerCount; d++) {
        for (int i = 0; i < cornerCount; i++) {
            int j = (i + d) % cornerCount;
            for (int k = i + 1; k != j; k = (k + 1) % cornerCount)
                DP[i][j] = max(DP[i][j], DP[i][k] + DP[k][j]);
            DP[i][j] += connected[i][j];
        }
    }
    cout << DP[0][cornerCount - 1] << endl;
    return 0;
}
