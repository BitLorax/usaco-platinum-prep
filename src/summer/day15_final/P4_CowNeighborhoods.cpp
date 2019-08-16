////
//// Created by WillJ on 7/19/2019.
////
//
//#include <iostream>
//#include <fstream>
//#include <algorithm>
//#include <vector>
//#include <set>
//
//#define INF 2000000000
//#define MAX_COWCNT 100000
//
//using namespace std;
//
//struct Side {
//    int x, y1, y2, mag, id;
//    bool operator<(const Side &a) const {
//        return x < a.x;
//    }
//};
//struct UnionFind {
//    int n;
//    vector<int> component;
//    vector<vector<int>> indices;
//    void construct(int size) {
//        n = size;
//        component = vector<int>(n + 1, 0);
//        indices = vector<vector<int>>(n + 1);
//        for (int i = 0; i <= n; i++) {
//            component[i] = i;
//            indices[i].push_back(i);
//        }
//    }
//    int find(int node) {
//        return component[node];
//    }
//    void join(int a, int b) {
//        if (indices[component[b]].size() > indices[component[a]].size()) {
//            int temp = a;
//            a = b; b = temp;
//        }
//        for (int j : indices[component[b]]) {
//            component[j] = component[a];
//            indices[component[a]].push_back(j);
//        }
//    }
//};
//
//int cowCount, dist;
//Side sides[MAX_COWCNT + 1];
//bool visited[MAX_COWCNT + 1];
//
//int intersect(Side a, Side b) {
//    return (a.y1 >= b.y1 && a.y1 <= b.y2) || (a.y2 >= b.y1 && a.y2 <= b.y2);
//}
//
//int main() {
//    cin >> cowCount >> dist;
//    for (int i = 0; i < cowCount; i++) {
//        int x, y; cin >> x >> y;
//        int x1 = x - dist, y1 = y;
//        int x2 = x + dist, y2 = y;
//        int dx1 = x1 + y1, dy1 = x1 - y1;
//        int dx2 = x2 + y2, dy2 = x2 - y2;
//        sides[i] = Side{dx1, dy1, dy2, 1, i};
//        sides[i + cowCount] = Side{dx2 + 1, dy1, dy2, -1, i};
//    }
//    sort(sides, sides + 2 * cowCount);
//
//    UnionFind uf{}; uf.construct(cowCount + 1);
//    multiset<Side> s;
//    for (int i = 0; i < 2 * cowCount; i++) {
//        int curX = sides[i].x;
//        while (curX == sides[i].x) {
//
//        }
//    }
//
//    return 0;
//}

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define INF 2000000000
#define MAX_COWCNT 100000

using namespace std;

struct UnionFind {
    int n;
    vector<int> component;
    vector<vector<int>> indices;
    void construct(int size) {
        n = size;
        component = vector<int>(n + 1, 0);
        indices = vector<vector<int>>(n + 1);
        for (int i = 0; i <= n; i++) {
            component[i] = i;
            indices[i].push_back(i);
        }
    }
    int find(int node) {
        return component[node];
    }
    void join(int a, int b) {
        if (indices[component[b]].size() > indices[component[a]].size()) {
            int temp = a;
            a = b; b = temp;
        }
        for (int j : indices[component[b]]) {
            component[j] = component[a];
            indices[component[a]].push_back(j);
        }
    }
};

struct Coord {
    int x, y;
    bool operator<(const Coord &a) const {
        return x < a.x;
    }
};

int getDist(Coord a, Coord b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

Coord cows[MAX_COWCNT + 1];
int size[MAX_COWCNT + 1];

int main() {
    int cowCount, dist; cin >> cowCount >> dist;
    for (int i = 0; i < cowCount; i++) {
        cin >> cows[i].x >> cows[i].y;
    }
    sort(cows, cows + cowCount);

    UnionFind uf{}; uf.construct(cowCount + 1);
    for (int i = 0; i < cowCount; i++) {
        for (int j = i + 1; j < cowCount; j++) {
            if (getDist(cows[i], cows[j]) - 9 * dist / 10 > dist) break;
            if (getDist(cows[i], cows[j]) <= dist) {
                if (uf.find(i) != uf.find(j)) uf.join(i, j);
            }
        }
    }

    int groupCount = 0;
    int maxSize = 0;
    for (int i = 0; i < cowCount; i++) {
        size[uf.component[i]]++;
    }
    for (int i = 0; i < cowCount; i++) {
        maxSize = max(maxSize, size[i]);
        if (size[i] > 0) groupCount++;
    }

    cout << groupCount << " " << maxSize;
    return 0;
}