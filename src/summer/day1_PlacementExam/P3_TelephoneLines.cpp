//
// Created by WillJ on 7/1/2019.
//

#include <iostream>
#include <vector>
#include <set>
#include <queue>

#define MAX_POLECNT 1000

using namespace std;

vector<pair<int, int>> connections[MAX_POLECNT + 1];

struct State {
    multiset<int> cables;
    //vector<bool> visited;
    int node;
    State(int node) {
        this->node = node;
        //visited.resize(MAX_POLECNT + 1);
    }
};

int main() {

    int poleCount, connectionCount, freeCount; cin >> poleCount >> connectionCount >> freeCount;
    for (int i = 0; i < connectionCount; i++) {
        int a, b, c; cin >> a >> b >> c;
        connections[a].push_back(make_pair(b, c));
        connections[b].push_back(make_pair(a, c));
    }

    int minCost = 1000001;

    int cheese = 0;

    queue<State> q;
    q.push(State{1});
    while (!q.empty()) {
        cheese++;
        if (cheese >= 1000000) break;
        State cur = q.front(); q.pop();
        //cur.visited[cur.node] = true;
        if (cur.node == poleCount) {
            minCost = min(minCost, *cur.cables.begin());
            continue;
        }
        for (pair<int, int> i : connections[cur.node]) {
            //if (cur.visited[i.first]) continue;
            State newState{i.first}; newState.cables = cur.cables; //newState.visited = cur.visited;
            newState.cables.insert(i.second);
            if (newState.cables.size() > freeCount + 1) {
                newState.cables.erase(newState.cables.begin());
            }
            q.push(newState);
        }
    }

    cout << ((minCost == 1000001) ? -1 : minCost) << endl;
    return 0;
}
