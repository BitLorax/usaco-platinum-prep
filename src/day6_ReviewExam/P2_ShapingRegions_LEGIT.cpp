//
// Created by WillJ on 10/14/2018.
//
//note: P2_ShapingRegions didn't use the correct method but still passed
//      this is an attempt to solve it with the correct method

#include <iostream>
#include <vector>

#define MAX_COLOR 2500

using namespace std;

struct Rectangle {
    int lx, ly, hx, hy, color;
};

int colors[MAX_COLOR];

bool validRect(Rectangle a) {
    return a.lx < a.hx && a.ly < a.hy;
}
bool inRect(Rectangle a, int x, int y) {
    return (x > a.lx && x < a.hx && y > a.ly && y < a.hy);
}
bool checkRectIntersect(Rectangle a, Rectangle b) {
    return (inRect(b, a.lx, a.ly) || inRect(b, a.lx, a.hy) || inRect(b, a.hx, a.ly) || inRect(b, a.hx, a.hy) || inRect(a, b.lx, b.ly) || inRect(a, b.lx, b.hy) || inRect(a, b.hx, b.ly) || inRect(a, b.hx, b.hy));
}

int main() {
    vector<Rectangle> rectangles;
    int width, height, rectangleCount; cin >> width >> height >> rectangleCount;
    Rectangle paper{0, 0, width, height, 1};
    rectangles.push_back(paper);
    for (int i = 1; i <= rectangleCount; i++) {
        int lx, ly, hx, hy, color; cin >> lx >> ly >> hx >> hy >> color;
        Rectangle newRect{lx, ly, hx, hy, color};
        for (int j = 0; j < i; j++) {
            Rectangle t = rectangles[j];
            if (!checkRectIntersect(newRect, t)) continue;

            Rectangle one{t.lx, t.ly, lx, t.hy, t.color};
            Rectangle two{lx, hy, hx, t.hy, t.color};
            Rectangle three{lx, t.ly, hx, ly, t.color};
            Rectangle four{hx, t.ly, t.hx, t.hy, t.color};

            if (validRect(one)) rectangles.push_back(one);
            if (validRect(two)) rectangles.push_back(two);
            if (validRect(three)) rectangles.push_back(three);
            if (validRect(four)) rectangles.push_back(four);
            rectangles.erase(rectangles.begin() + j);
        }
        rectangles.push_back(newRect);
    }
    for (int i = 0; i < rectangles.size(); i++) {
        colors[rectangles[i].color] += ((rectangles[i].hx - rectangles[i].lx) * (rectangles[i].hy - rectangles[i].ly));
    }
    for (int i = 0; i < MAX_COLOR; i++) {
        if (colors[i] != 0) cout << i << " " << colors[i] << endl;
    }
    return 0;
}

