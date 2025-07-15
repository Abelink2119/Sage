#include <iostream>
using namespace std;

char board[3][3];
char currentPlayer;

void InitializeBoard() {
    char c = '1';
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = c++;
}

void PrintBoard() {
    cout << endl;
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "---+---+---" << endl;
    }
    cout << endl;
}

bool CheckWin() {
    // Rows & Columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == currentPlayer &&
            board[i][1] == currentPlayer &&
            board[i][2] == currentPlayer)
            return true;
        if (board[0][i] == currentPlayer &&
            board[1][i] == currentPlayer &&
            board[2][i] == currentPlayer)
            return true;
    }
    // Diagonals
    if (board[0][0] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][2] == currentPlayer)
        return true;
    if (board[0][2] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][0] == currentPlayer)
        return true;

    return false;
}

bool CheckDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
    return true;
}

void SwitchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

int main() {
    InitializeBoard();
    currentPlayer = 'X';

    while (true) {
        PrintBoard();
        cout << "Player " << currentPlayer << ", enter a number (1 - 9): ";
        int move;
        cin >> move;

        if (move < 1 || move > 9) {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        int row = (move - 1) / 3;
        int col = (move - 1) % 3;

        if (board[row][col] == 'X' || board[row][col] == 'O') {
            cout << "Spot already taken! Try again.\n";
            continue;
        }

        board[row][col] = currentPlayer;

        if (CheckWin()) {
            PrintBoard();
            cout << "?? Player " << currentPlayer << " wins!\n";
            break;
        }

        if (CheckDraw()) {
            PrintBoard();
            cout << "It's a draw!\n";
            break;
        }

        SwitchPlayer();
    }

    return 0;
}
