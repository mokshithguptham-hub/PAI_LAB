#include <iostream>
using namespace std;

int main() {
    int dirtA, dirtB, pos;
    cout << "Enter dirt status of A (0-clean, 1-dirty): ";
    cin >> dirtA;
    cout << "Enter dirt status of B (0-clean, 1-dirty): ";
    cin >> dirtB;
    cout << "Enter starting position (0-A, 1-B): ";
    cin >> pos;

    cout << "\nVacuum Cleaner Actions:\n";

    // Clean current position
    if(pos == 0 && dirtA == 1) {
        cout << "Clean A\n";
        dirtA = 0;
    }
    else if(pos == 1 && dirtB == 1) {
        cout << "Clean B\n";
        dirtB = 0;
    }

    // Move to other position if dirty
    if(pos == 0 && dirtB == 1) {
        cout << "Move Right to B\n";
        cout << "Clean B\n";
        dirtB = 0;
    }
    else if(pos == 1 && dirtA == 1) {
        cout << "Move Left to A\n";
        cout << "Clean A\n";
        dirtA = 0;
    }

    cout << "\nAll squares are clean.\n";
    return 0;
}
