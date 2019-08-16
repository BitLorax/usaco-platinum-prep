//
// Created by WillJ on 7/1/2019.
//

#include <iostream>
#include <fstream>
#include <queue>

#define INF 2000000000
#define MAX_SIZE 100
#define MAX_LEN 15

using namespace std;

bool map[MAX_SIZE][MAX_SIZE];
int DP[MAX_SIZE][MAX_SIZE][MAX_LEN + 1];

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

struct State {
    int x, y, len, count;
};

int main() {
    int height, width, len; cin >> height >> width >> len;
    for (int i = 0; i < height; i++) {
        string row; cin >> row;
        for (int j = 0; j < width; j++) {
            map[j][i] = row[j] == '*';
        }
    }
    int sX, sY, eX, eY; cin >> sY >> sX >> eY >> eX;
    sX--; sY--; eX--; eY--;

    DP[sX][sY][0] = 1;
    for (int k = 0; k < len; k++) {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                if (DP[i][j][k] == 0) continue;
                for (int l = 0; l < 4; l++) {
                    if (i + dx[l] < 0 || i + dx[l] >= width || j + dy[l] < 0 || j + dy[l] >= height ||
                        map[i + dx[l]][j + dy[l]])
                        continue;
                    DP[i + dx[l]][j + dy[l]][k + 1] += DP[i][j][k];
                }
            }
        }
    }

    cout << DP[eX][eY][len];
    return 0;
}
