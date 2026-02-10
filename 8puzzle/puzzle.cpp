#include <bits/stdc++.h>
using namespace std;

struct State {
    vector<vector<int>> board;
    int g, h, f;
    State* parent;
};

// Heuristic: Manhattan distance
int calculateHeuristic(vector<vector<int>> &board, vector<vector<int>> &goal) {
    int h = 0;
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            if(board[i][j] != 0) {
                int val = board[i][j];
                for(int x=0; x<3; x++) {
                    for(int y=0; y<3; y++) {
                        if(goal[x][y] == val) {
                            h += abs(i-x) + abs(j-y);
                        }
                    }
                }
            }
        }
    }
    return h;
}

// Generate neighbors
vector<State*> getNeighbors(State* current, vector<vector<int>> &goal) {
    vector<State*> neighbors;
    int x, y;
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            if(current->board[i][j] == 0) { x=i; y=j; }

    int dx[] = {-1,1,0,0};
    int dy[] = {0,0,-1,1};

    for(int k=0; k<4; k++) {
        int nx = x+dx[k], ny = y+dy[k];
        if(nx>=0 && nx<3 && ny>=0 && ny<3) {
            State* newState = new State;
            newState->board = current->board;
            swap(newState->board[x][y], newState->board[nx][ny]);
            newState->g = current->g + 1;
            newState->h = calculateHeuristic(newState->board, goal);
            newState->f = newState->g + newState->h;
            newState->parent = current;
            neighbors.push_back(newState);
        }
    }
    return neighbors;
}

// Print board
void printBoard(vector<vector<int>> &board) {
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "------\n";
}

// Reconstruct path
void printSolution(State* goalState) {
    vector<State*> path;
    while(goalState != nullptr) {
        path.push_back(goalState);
        goalState = goalState->parent;
    }
    reverse(path.begin(), path.end());
    for(auto s : path) {
        printBoard(s->board);
    }
}

// Check solvability
bool isSolvable(vector<vector<int>> &board) {
    vector<int> arr;
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            if(board[i][j] != 0) arr.push_back(board[i][j]);

    int inv = 0;
    for(int i=0; i<arr.size(); i++) {
        for(int j=i+1; j<arr.size(); j++) {
            if(arr[i] > arr[j]) inv++;
        }
    }
    return (inv % 2 == 0);
}

// A* Search
void solvePuzzle(vector<vector<int>> start, vector<vector<int>> goal) {
    auto cmp = [](State* a, State* b){ return a->f > b->f; };
    priority_queue<State*, vector<State*>, decltype(cmp)> openSet(cmp);

    State* root = new State{start, 0, calculateHeuristic(start, goal), 0, nullptr};
    root->f = root->g + root->h;
    openSet.push(root);

    while(!openSet.empty()) {
        State* current = openSet.top();
        openSet.pop();

        if(current->h == 0) { // Goal reached
            cout << "Solved in " << current->g << " moves\n";
            printSolution(current);
            return;
        }

        vector<State*> neighbors = getNeighbors(current, goal);
        for(auto neighbor : neighbors) {
            openSet.push(neighbor);
        }
    }
    cout << "No solution found (search exhausted).\n";
}

int main() {
    vector<vector<int>> start(3, vector<int>(3));
    vector<vector<int>> goal(3, vector<int>(3));

    cout << "Enter start state (3x3, use 0 for blank):\n";
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            cin >> start[i][j];

    cout << "Enter goal state (3x3, use 0 for blank):\n";
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            cin >> goal[i][j];

    if(!isSolvable(start)) {
        cout << "No solution exists for the given start state.\n";
        return 0;
    }

    solvePuzzle(start, goal);
    return 0;
}
