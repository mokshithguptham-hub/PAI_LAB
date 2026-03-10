#include <iostream>
using namespace std;

char board[3][3] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'}
};

void showBoard() {
    cout << "\n";
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            cout << board[i][j];
            if(j<2) cout << " | ";
        }
        if(i<2) cout << "\n---------\n";
    }
    cout << "\n\n";
}

bool checkWin() {
    // rows
    for(int i=0;i<3;i++)
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2])
            return true;

    // columns
    for(int i=0;i<3;i++)
        if(board[0][i]==board[1][i] && board[1][i]==board[2][i])
            return true;

    // diagonals
    if(board[0][0]==board[1][1] && board[1][1]==board[2][2])
        return true;

    if(board[0][2]==board[1][1] && board[1][1]==board[2][0])
        return true;

    return false;
}

int main() {
    int choice;
    char player = 'X';
    int row, col;
    int moves = 0;

    while(true) {
        showBoard();
        cout << "Player " << player << ", enter position (1-9): ";
        cin >> choice;

        row = (choice-1)/3;
        col = (choice-1)%3;

        if(board[row][col] != 'X' && board[row][col] != 'O') {
            board[row][col] = player;
            moves++;

            if(checkWin()) {
                showBoard();
                cout << "Player " << player << " wins!\n";
                break;
            }

            if(moves == 9) {
                showBoard();
                cout << "Game Draw!\n";
                break;
            }

            player = (player=='X') ? 'O' : 'X';
        }
        else {
            cout << "Invalid move! Try again.\n";
        }
    }

    return 0;
}
