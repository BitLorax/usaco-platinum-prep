//
// Created by WillJ on 7/4/2019.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#define INF 2000000000
#define MAX_LEN 1000000

using namespace std;

string str, pat;
int fail[MAX_LEN];
int pPats[MAX_LEN];

void construct() {
    fail[0] = -1;
    for (int i = 1; i <= pat.length(); i++) {
        fail[i] = fail[i - 1];
        while (fail[i] > -1 && pat[i - 1] != pat[fail[i]]) fail[i] = fail[fail[i]];
        fail[i]++;
    }
}

int main() {
    cin >> str >> pat;
    construct();

    int pPat = 0;
    vector<pair<char, int>> stack;

    for (int pStr = 0; pStr < str.length(); pStr++) {
        while (pPat >= 0 && pat[pPat] != str[pStr]) pPat = fail[pPat];
        pPat++;
        stack.push_back(make_pair(str[pStr], pPat));
        if (pPat == pat.length()) {
            for (int j = 0; j < pat.length(); j++) stack.pop_back();

            pPat = stack.rbegin()->second;
        }
    }

    for (pair<char, int> i : stack) cout << i.first;
    cout << endl;
    return 0;
}
