#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
using namespace std;

vector<string> leftWords;   // words on LHS
vector<string> rightWords;  // words on RHS (can be multiple)
map<char,int> assign;       // letter → digit
bool used[10];              // digit usage
vector<char> letters;       // unique letters
vector<map<char,int>> solutions; // store all solutions

// Evaluate a word given current assignment
long getValue(const string &w) {
    long val = 0;
    for (char c : w) {
        if (assign.find(c) == assign.end()) return -1; // not yet assigned
        val = val * 10 + assign[c];
    }
    return val;
}

// Check if current assignment satisfies equation
bool checkEquation() {
    long lhsSum = 0;
    for (string w : leftWords) {
        long val = getValue(w);
        if (val < 0) return false;
        lhsSum += val;
    }
    long rhsSum = 0;
    for (string w : rightWords) {
        long val = getValue(w);
        if (val < 0) return false;
        rhsSum += val;
    }
    return (lhsSum == rhsSum);
}

// Recursive backtracking
void solve(int idx) {
    if (idx == letters.size()) {
        if (checkEquation()) {
            solutions.push_back(assign);
        }
        return;
    }

    char c = letters[idx];
    for (int d = 0; d <= 9; d++) {
        if (used[d]) continue;
        // Leading letters cannot be zero
        bool isLeading = false;
        for (string w : leftWords) if (w[0] == c) isLeading = true;
        for (string w : rightWords) if (w[0] == c) isLeading = true;
        if (isLeading && d == 0) continue;

        assign[c] = d;
        used[d] = true;

        solve(idx+1);

        // backtrack
        assign.erase(c);
        used[d] = false;
    }
}

int main() {
    cout << "Enter crypto-arithmetic equation (example: SEND+MORE=MONEY or FORTY+TEN+TEN=SIXTY): ";
    string input;
    cin >> input;

    // Split input into LHS and RHS
    size_t eqPos = input.find('=');
    if (eqPos == string::npos) {
        cout << "Invalid equation format.\n";
        return 0;
    }
    string lhs = input.substr(0, eqPos);
    string rhs = input.substr(eqPos+1);

    // Split LHS by '+'
    size_t pos = 0;
    while ((pos = lhs.find('+')) != string::npos) {
        leftWords.push_back(lhs.substr(0, pos));
        lhs.erase(0, pos+1);
    }
    leftWords.push_back(lhs);

    // Split RHS by '+'
    pos = 0;
    while ((pos = rhs.find('+')) != string::npos) {
        rightWords.push_back(rhs.substr(0, pos));
        rhs.erase(0, pos+1);
    }
    rightWords.push_back(rhs);

    // Collect unique letters
    set<char> s;
    for (string w : leftWords) for (char c : w) s.insert(c);
    for (string w : rightWords) for (char c : w) s.insert(c);
    letters.assign(s.begin(), s.end());

    if (letters.size() > 10) {
        cout << "Error: More than 10 unique letters. Cannot solve.\n";
        return 0;
    }

    // Initialize used array
    for (int i = 0; i < 10; i++) used[i] = false;

    solve(0);

    if (solutions.empty()) {
        cout << "No solution exists.\n";
    } else {
        cout << "Solutions found: " << solutions.size() << "\n";
        for (auto &sol : solutions) {
            for (auto &p : sol) cout << p.first << "=" << p.second << " ";
            cout << endl;

            long lhsSum = 0;
            for (int i = 0; i < leftWords.size(); i++) {
                long val = 0;
                for (char c : leftWords[i]) val = val*10 + sol[c];
                lhsSum += val;
                cout << val;
                if (i < leftWords.size()-1) cout << " + ";
            }
            cout << " = ";

            long rhsSum = 0;
            for (int i = 0; i < rightWords.size(); i++) {
                long val = 0;
                for (char c : rightWords[i]) val = val*10 + sol[c];
                rhsSum += val;
                cout << val;
                if (i < rightWords.size()-1) cout << " + ";
            }
            cout << endl;
            cout << "-----------------\n";
        }
    }
    return 0;
}