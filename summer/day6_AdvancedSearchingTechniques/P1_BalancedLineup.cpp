//
// Created by WillJ on 7/8/2019.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#define INF 2000000000
#define MAX_COWCNT 50000
#define LOG 20

using namespace std;

int cows[MAX_COWCNT + 1];
int flipped[MAX_COWCNT + 1];

struct RMQ {
    int n;
    vector<vector<int>> maxs;
    void preprocess(int arr[], int size) {
        n = size;
        maxs = vector<vector<int>>(MAX_COWCNT + 1, vector<int>(LOG));
        for (int i = 0; i < n; i++) maxs[i][0] = i;
        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; (i + (1 << j)) <= n; i++) {
                if (arr[maxs[i][j - 1]] > arr[maxs[i + (1 << (j - 1))][j - 1]]) maxs[i][j] = maxs[i][j - 1];
                else maxs[i][j] = maxs[i + (1 << (j - 1))][j - 1];
            }
        }
    }
    int query(int arr[], int lo, int hi) {
        int i = (int)(log2(hi - lo + 1));
        if (arr[maxs[lo][i]] >= arr[maxs[hi - (1 << i) + 1][i]]) return maxs[lo][i];
        return maxs[hi - (1 << i) + 1][i];
    }
};

int main() {
    int cowCount, queryCount; cin >> cowCount >> queryCount;
    for (int i = 0; i < cowCount; i++) {
        cin >> cows[i];
        flipped[i] = -cows[i];
    }
    RMQ rmqMax{}; RMQ rmqMin{};
    rmqMax.preprocess(cows, cowCount); rmqMin.preprocess(flipped, cowCount);
    for (int i = 0; i < queryCount; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        int minVal = flipped[rmqMin.query(flipped, a, b)] * -1;
        int maxVal = cows[rmqMax.query(cows, a, b)];
        cout << maxVal - minVal << endl;
    }
    return 0;
}
