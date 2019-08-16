//
// Created by WillJ on 12/2/2018.
//

#include <iostream>
#include <map>

#define MAX_GANGCNT 100

using namespace std;

map<int, int> gangInfo;

int main() {
    int cowCount, gangCount; cin >> cowCount >> gangCount;
    for (int i = 1; i <= gangCount; i++) {
        int a; cin >> a;
        gangInfo.insert(a, i);
    }


    return 0;
}
