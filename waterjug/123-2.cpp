#include <bits/stdc++.h>
using namespace std;

struct State {
    int jug1, jug2;
    string path;
};

// Function to check if we have reached the target
bool isGoal(State s, int target) {
    return (s.jug1 == target || s.jug2 == target);
}

// BFS function to find the steps
void waterJug(int jug1Cap, int jug2Cap, int target) {
    set<pair<int,int>> visited;
    queue<State> q;

    State start = {0, 0, ""};
    q.push(start);
    visited.insert({0,0});

    while(!q.empty()) {
        State curr = q.front(); q.pop();

        if(isGoal(curr, target)) {
            cout << "Solution found:\n";
            cout << curr.path;
            cout << "Final state: (" << curr.jug1 << ", " << curr.jug2 << ")\n";
            return;
        }

        // 1. Fill Jug1
        if(curr.jug1 < jug1Cap) {
            State next = {jug1Cap, curr.jug2, curr.path + "Fill Jug1 -> (" + to_string(jug1Cap) + ", " + to_string(curr.jug2) + ")\n"};
            if(visited.find({next.jug1, next.jug2}) == visited.end()) {
                visited.insert({next.jug1, next.jug2});
                q.push(next);
            }
        }

        // 2. Fill Jug2
        if(curr.jug2 < jug2Cap) {
            State next = {curr.jug1, jug2Cap, curr.path + "Fill Jug2 -> (" + to_string(curr.jug1) + ", " + to_string(jug2Cap) + ")\n"};
            if(visited.find({next.jug1, next.jug2}) == visited.end()) {
                visited.insert({next.jug1, next.jug2});
                q.push(next);
            }
        }

        // 3. Empty Jug1
        if(curr.jug1 > 0) {
            State next = {0, curr.jug2, curr.path + "Empty Jug1 -> (" + to_string(0) + ", " + to_string(curr.jug2) + ")\n"};
            if(visited.find({next.jug1, next.jug2}) == visited.end()) {
                visited.insert({next.jug1, next.jug2});
                q.push(next);
            }
        }

        // 4. Empty Jug2
        if(curr.jug2 > 0) {
            State next = {curr.jug1, 0, curr.path + "Empty Jug2 -> (" + to_string(curr.jug1) + ", " + to_string(0) + ")\n"};
            if(visited.find({next.jug1, next.jug2}) == visited.end()) {
                visited.insert({next.jug1, next.jug2});
                q.push(next);
            }
        }

        // 5. Pour Jug1 -> Jug2
        if(curr.jug1 > 0 && curr.jug2 < jug2Cap) {
            int pour = min(curr.jug1, jug2Cap - curr.jug2);
            State next = {curr.jug1 - pour, curr.jug2 + pour,
                          curr.path + "Pour Jug1 -> Jug2 -> (" + to_string(curr.jug1 - pour) + ", " + to_string(curr.jug2 + pour) + ")\n"};
            if(visited.find({next.jug1, next.jug2}) == visited.end()) {
                visited.insert({next.jug1, next.jug2});
                q.push(next);
            }
        }

        // 6. Pour Jug2 -> Jug1
        if(curr.jug2 > 0 && curr.jug1 < jug1Cap) {
            int pour = min(curr.jug2, jug1Cap - curr.jug1);
            State next = {curr.jug1 + pour, curr.jug2 - pour,
                          curr.path + "Pour Jug2 -> Jug1 -> (" + to_string(curr.jug1 + pour) + ", " + to_string(curr.jug2 - pour) + ")\n"};
            if(visited.find({next.jug1, next.jug2}) == visited.end()) {
                visited.insert({next.jug1, next.jug2});
                q.push(next);
            }
        }
    }

    cout << "No solution exists.\n";
}

int main() {
    int jug1, jug2, target;
    cout << "Enter capacity of Jug1: ";
    cin >> jug1;
    cout << "Enter capacity of Jug2: ";
    cin >> jug2;
    cout << "Enter target amount: ";
    cin >> target;

    waterJug(jug1, jug2, target);
    return 0;
}
