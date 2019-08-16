//
// Created by WillJ on 7/2/2019.
//

#include <iostream>
#include <fstream>
#include <set>
#include <cmath>

#define INF 2000000000
#define MAX_POINTCNT 1000

using namespace std;

struct Coord {
    double x, y;
    bool operator<(const Coord &a) const {
        if (x == a.x) return y < a.y;
        return x < a.x;
    }
};
struct Vec {
    double x, y;
};
struct Line {
    int A, B, C; //Ax + By = C
    bool operator<(const Line &a) const {
        if (A == a.A) {
            if (B == a.B) return C < a.C;
            return B < a.B;
        }
        return A < a.A;
    }
};

int pointCount;
Coord points[MAX_POINTCNT];
set<Coord> pointSet;
set<Line> validLines;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

Line calcLine(Coord one, Coord two) {
    int A = two.y - one.y; int B = one.x - two.x;
    int C = A * one.x + B * one.y;
    return Line{A, B, C};
}

Coord getReflect(Coord pt, Line sym) {
    Vec n{(double)sym.A, (double)sym.B};
    double change = (sym.A * pt.x + sym.B * pt.y - sym.C) / (sym.A * sym.A + sym.B * sym.B);
    Vec delta{n.x * change, n.y * change};
    return Coord{pt.x - 2 * delta.x, pt.y - 2 * delta.y};
}

bool calcSym(Line sym) {
    for (int j = 0; j < pointCount; j++) {
        Coord reflected = getReflect(points[j], sym);

        if (reflected.x - floor(reflected.x) < 10e-8) reflected.x = floor(reflected.x);
        if (ceil(reflected.x) - reflected.x < 10e-8) reflected.x = ceil(reflected.x);
        if (reflected.y - floor(reflected.y) < 10e-8) reflected.y = floor(reflected.y);
        if (ceil(reflected.y) - reflected.y < 10e-8) reflected.y = ceil(reflected.y);

        if (floor(reflected.x) != reflected.x || floor(reflected.y) != reflected.y) return false;

        Coord search = *pointSet.lower_bound(reflected);
        if (search.x != reflected.x || search.y != reflected.y) return false;
    }
    return true;
}

void findSym(int fixed) {
    for (int i = fixed + 1; i < pointCount; i++) {
        Coord symOne{(points[i].x + points[fixed].x) / 2,
                     (points[i].y + points[fixed].y) / 2};
        Coord symTwo{symOne.x + points[i].y - points[fixed].y,
                     symOne.y + points[fixed].x - points[i].x};
        Line sym = calcLine(symOne, symTwo);
        int k = gcd(sym.A, gcd(sym.B, sym.C));
        sym.A /= k; sym.B /= k; sym.C /= k;

        if (calcSym(sym)) validLines.insert(sym);
    }
}

int main() {
    cin >> pointCount;
    for (int i = 0; i < pointCount; i++) {
        cin >> points[i].x >> points[i].y;
        points[i].x *= 2; points[i].y *= 2;
        pointSet.insert(points[i]);
    }
    findSym(0); findSym(1);
    Line sym = calcLine(points[1], points[0]);
    if (calcSym(sym)) validLines.insert(sym);

    cout << validLines.size() << endl;
    return 0;
}
