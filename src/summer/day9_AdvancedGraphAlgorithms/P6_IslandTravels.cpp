//
// Created by WillJ on 7/11/2019.
//

#include <iostream>
#include <fstream>
#include <queue>

#define INF 1000000000
#define MAX_SIDELEN 50
#define MAX_ISLANDCNT 15

using namespace std;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int height, width;
char grid[MAX_SIDELEN + 1][MAX_SIDELEN + 1];
int id[MAX_SIDELEN + 1][MAX_SIDELEN + 1];
bool visited[MAX_SIDELEN + 1][MAX_SIDELEN + 1];
int dists[MAX_ISLANDCNT + 1][MAX_ISLANDCNT + 1];
int DP[1 << (MAX_ISLANDCNT + 1)][MAX_ISLANDCNT + 1];

struct State {
    int x, y, dist;
};

void floodfill(int x, int y, int curId) {
    if (x < 0 || x >= width || y < 0 || y >= height) return;
    if (grid[x][y] != 'X' || id[x][y] != -1) return;
    id[x][y] = curId;
    for (int i = 0; i < 4; i++) {
        floodfill(x + dx[i], y + dy[i], curId);
    }
}
void getDists(int curId) {
    queue<State> q;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (id[i][j] == curId) q.push(State{i, j, 0});
            visited[i][j] = false;
        }
    }

    while (!q.empty()) {
        State cur = q.front(); q.pop();
        if (cur.x < 0 || cur.x >= width || cur.y < 0 || cur.y >= width) continue;
        if (grid[cur.x][cur.y] == '.') continue;
        if (visited[cur.x][cur.y]) continue;
        visited[cur.x][cur.y] = true;

        if (id[cur.x][cur.y] != -1 && id[cur.x][cur.y] != curId) {
            if (dists[curId][id[cur.x][cur.y]] == INF)
                dists[curId][id[cur.x][cur.y]] = cur.dist - 1;
            continue;
        }

        for (int i = 0; i < 4; i++) {
            q.push(State{cur.x + dx[i], cur.y + dy[i], cur.dist + 1});
        }
    }
}

int main() {
    cin >> height >> width;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cin >> grid[j][i];
            id[j][i] = -1;
        }
    }
    int islandCount = 0;
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            if (grid[i][j] == 'X' && id[i][j] == -1) floodfill(i, j, islandCount++);
    for (int i = 0; i < islandCount; i++)
        for (int j = 0; j < islandCount; j++)
            dists[i][j] = INF;
    for (int i = 0; i < islandCount; i++) getDists(i);
    for (int l = 0; l < islandCount; l++) {
        for (int i = 0; i < islandCount; i++) {
            for (int j = 0; j < islandCount; j++) {
                dists[i][j] = min(dists[i][j], dists[i][l] + dists[l][j]);
            }
        }
    }

    for (int i = 0; i <= (1 << islandCount); i++)
        for (int j = 0; j < islandCount; j++) DP[i][j] = INF;
    for (int j = 0; j < islandCount; j++)
        DP[(1 << j)][j] = 0;

    for (int i = 1; i < (1 << islandCount); i++) {
        for (int j = 0; j < islandCount; j++) {
            if ((i & (1 << j)) == 0) continue;
            for (int k = 0; k < islandCount; k++) {
                if (dists[k][j] == 0) continue;
                DP[i][j] = min(DP[i][j], DP[i ^ (1 << j)][k] + dists[k][j]);
            }
        }
    }

    int minDist = INF;
    for (int i = 0; i < islandCount; i++) minDist = min(minDist, DP[(1 << islandCount) - 1][i]);
    cout << minDist << endl;
    return 0;
}
