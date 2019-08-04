//
// Created by WillJ on 9/23/2018.
//
#include <iostream>
#include <algorithm>

#define INF 2000000000

using namespace std;

struct Coord {
    int row, x;
    bool operator<(const Coord &a) const {
        if (a.row == row) {
            return x > a.x;
        }
        return row > a.row;
    }
};

int calcMinDist(Coord &from, Coord &to) {
    if (from.row == to.row) return abs(from.x - to.x);
    if (from.row > to.row) return calcMinDist(to, from);
    if (from.x % 2 == 0) {
        Coord left{from.row, from.x - 1}; Coord right{from.row, from.x + 1};
        return min(calcMinDist(left, to), calcMinDist(right, to)) + 1;
    }
    int down = 2 * abs(from.row - to.row) - 1;
    int lo = from.x + 1, hi = from.x + 2 * abs(from.row - to.row) - 1;
    if (to.x < lo) return down + lo - to.x;
    if (to.x > hi) return down + to.x - hi;
    return (to.x % 2 == 0) ? down : down + 1;
}

int main() {
    int rowCount, exitCount; cin >> rowCount >> exitCount;
    Coord start{-1, -1}; cin >> start.row >> start.x;
    int minDist = INF;
    Coord closest{INF, INF};
    for (int ii = 0; ii < exitCount; ii++) {
        Coord exit{-1, -1}; cin >> exit.row >> exit.x;
        int i = calcMinDist(start, exit);
        if (i < minDist || (i == minDist && ((exit.row < closest.row) || (exit.row == closest.row && exit.x < closest.x)))) {
            minDist = i;
            closest = exit;
        }
    }
    cout << closest.row << " " << closest.x << endl;
    cout << minDist + 1 << endl;
    return 0;
}
