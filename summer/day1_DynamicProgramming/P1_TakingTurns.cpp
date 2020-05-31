//
// Created by WillJ on 7/1/2019.
//

#include <iostream>
#include <fstream>

#define INF 2000000000
#define MAX_BALECNT 700000

using namespace std;

long long bales[MAX_BALECNT];

long long DPSelf[MAX_BALECNT + 1];
long long DPOppo[MAX_BALECNT + 1];

int main() {
    long long baleCount; cin >> baleCount;
    for (long long i = 0; i < baleCount; i++) {
        cin >> bales[i];
    }

    for (long long i = baleCount - 1; i >= 0; i--) {

        DPSelf[i] = DPSelf[i + 1]; DPOppo[i] = DPOppo[i + 1];
        long long gain = bales[i] + DPOppo[i + 1];
        if (gain >= DPSelf[i]) {
            DPSelf[i] = gain;
            DPOppo[i] = DPSelf[i + 1];
        }
    }
    cout << DPSelf[0] << " " << DPOppo[0] << endl;
    return 0;
}