#include <iostream>
#include <queue>
#include <set>
using namespace std;

struct State {
    int x, y; // amounts in jug1 and jug2
};

void waterJug(int jug1, int jug2, int target) {
    queue<State> q;
    set<pair<int,int>> visited;

    q.push({0,0});
    visited.insert({0,0});

    while (!q.empty()) {
        State cur = q.front(); q.pop();

        int a = cur.x, b = cur.y;
        cout << "(" << a << "," << b << ")\n";

        if (a == target || b == target) {
            cout << "Target reached!\n";
            return;
        }

        // Possible moves
        vector<State> nextStates = {
            {jug1, b},        // fill jug1
            {a, jug2},        // fill jug2
            {0, b},           // empty jug1
            {a, 0},           // empty jug2
            {max(0, a-(jug2-b)), min(jug2, b+a)}, // pour jug1 ? jug2
            {min(jug1, a+b), max(0, b-(jug1-a))}  // pour jug2 ? jug1
        };

        for (auto ns : nextStates) {
            if (visited.find({ns.x, ns.y}) == visited.end()) {
                visited.insert({ns.x, ns.y});
                q.push(ns);
            }
        }
    }
    cout << "No solution found.\n";
}

int main() {
    int jug1, jug2, target;
    cout << "Enter capacity of jug1, jug2 and target: ";
    cin >> jug1 >> jug2 >> target;

    if (target > max(jug1, jug2)) {
        cout << "Target cannot be greater than jug capacities.\n";
        return 0;
    }

    waterJug(jug1, jug2, target);
    return 0;
}