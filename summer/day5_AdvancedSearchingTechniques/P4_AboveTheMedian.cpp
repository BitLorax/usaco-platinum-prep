//
// Created by WillJ on 7/5/2019.
//

#include <iostream>
#include <fstream>

#define INF 2000000000
#define MAX_COWCNT 100000

using namespace std;

int cowCount, req;
int cows[MAX_COWCNT + 1];
long long fenwick[2 * MAX_COWCNT + 1];

struct Fenwicks {
    int query(int index) {
        index += MAX_COWCNT + 1;
        int ans = 0;
        for (; index > 0; index -= index&-index) ans += fenwick[index];
        return ans;
    }
    void update(int index, int add) {
        index += MAX_COWCNT + 1;
        for (; index < 2 * MAX_COWCNT + 1; index += index&-index) {
            fenwick[index] += add;
        }
    }
};

int main() {
    cin >> cowCount >> req;
    for (int i = 0; i < cowCount; i++) {
        long long a; cin >> a;
        cows[i] = ((a >= req) ? 1 : -1);
    }
    Fenwicks f{};
    f.update(0, 1);
    long long ans = 0, sum = 0;
    for (int i = 0; i < cowCount; i++) {
        sum += cows[i];
        ans += f.query(sum);
        f.update(sum, 1);
    }

    cout << ans << endl;
    return 0;
}
