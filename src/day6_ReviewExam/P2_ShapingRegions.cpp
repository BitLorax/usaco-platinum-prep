//
// Created by WillJ on 10/14/2018.
//
#include <iostream>

#define MAX_COLOR 2500
#define SIDELEN 800

using namespace std;

int paper[SIDELEN][SIDELEN];
int colors[MAX_COLOR];

int main() {
    int width, height, rectangleCount; cin >> width >> height >> rectangleCount;
    for (int i = 0; i < rectangleCount; i++) {
        int llx, lly, urx, ury, color; cin >> llx >> lly >> urx >> ury >> color; color--;
        for (int j = llx; j < urx; j++) {
            for (int k = lly; k < ury; k++) {
                paper[j][k] = color;
            }
        }
    }
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            colors[paper[i][j]]++;
        }
    }
    for (int i = 0; i < MAX_COLOR; i++) {
        if (colors[i] != 0) cout << i + 1 << " " << colors[i] << endl;
    }
    return 0;
}

