//
// Created by WillJ on 10/14/2018.
//
#include <iostream>

#define MAX_SIDELEN 250

using namespace std;

bool field[MAX_SIDELEN][MAX_SIDELEN];
int squares[MAX_SIDELEN];

int main() {
    int sideLen; cin >> sideLen;
    for (int i = 0; i < sideLen; i++) {
        string row; cin >> row;
        for (int j = 0; j < sideLen; j++) {
            field[j][i] = (row[j] == '1');
        }
    }
    for (int len = 2; len <= sideLen; len++) {
        for (int left = 0; left + len <= sideLen; left++) {
            int sum = 0;
            for (int top = 0; top + len <= sideLen; top++) {
                if (top == 0) { //build initial square
                    for (int i = left; i < left + len; i++) {
                        for (int j = 0; j < len; j++) {
                            sum += field[i][j];
                        }
                    }
                } else {
                    for (int i = left; i < left + len; i++) {
                        sum -= field[i][top - 1];
                        sum += field[i][top + len - 1];
                    }
                }
                if (sum == len * len) squares[len]++;
            }
        }
    }

    for (int i = 2; i <= sideLen; i++) {
        if (squares[i] != 0) cout << i << " " << squares[i] << endl;
        else break;
    }

    return 0;
}
/*
 * int horozontal = 0;
        for (int i = 0; i < len; i++) horozontal += field[i][0];
 *
 * int sum = horozontal;
            int right = left + len - 1;
            if (left == 0) { //build the initial square
                for (int i = 1; i < len; i++) {
                    for (int j = 0; j < len; j++) {
                        sum += field[j][i];
                    }
                }
            } else { //sliding window

            }
            if (sum == len * len) squares[len]++;
 */
