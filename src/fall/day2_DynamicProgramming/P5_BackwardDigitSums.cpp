//
// Created by WillJ on 9/20/2018.
//
#include <iostream>
#include <vector>

#define MAX_DIGITCNT 10

using namespace std;

int digitCount, sum;
long long choose[MAX_DIGITCNT + 1][MAX_DIGITCNT + 1];
vector<int> ans;
bool complete;

bool contains(int target, vector<int> nums) {
    for (int i : nums) {
        if (i == target) return true;
    }
    return false;
}
int calcSum(vector<int> &nums) {
    int sum = 0;
    for (int i = 0; i < nums.size(); i++) {
        sum += choose[nums.size() - 1][i] * nums[i];
    }
    return sum;
}

void getComb(int currNum, vector<int> &nums) {
    if (complete) return;
    if (currNum == digitCount) {
        if (calcSum(nums) == sum) {
            for (int i : nums) {
                cout << i << " ";
                complete = true;
            }
        }
    } else {
        for (int i = 1; i <= digitCount; i++) {
            if (!contains(i, nums)) {
                vector<int> newNums;
                newNums.assign(nums.begin(), nums.end());
                newNums.push_back(i);
                getComb(currNum + 1, newNums);
            }
        }
    }
}

int main() {
    cin >> digitCount >> sum;
    for (int i = 0; i <= digitCount; i++) {
        for (int j = 0; j <= digitCount; j++) {
            if (i == 0 || j == 0 || j == i) choose[i][j] = 1;
            else choose[i][j] = choose[i - 1][j] + choose[i - 1][j - 1];
        }
    }
    vector<int> a;
    getComb(0, a);
    return 0;
}
