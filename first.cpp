#include <iostream>
#include <vector>

using namespace std;

const int ROWS = 5;
const int COLS = 5;
const char EMPTY = '.';
const char PLAYER1 = 'X';
const char PLAYER2 = 'O';

// Initialize board with empty cells
void initializeBoard(vector<vector<char> >& board) {
    board.assign(ROWS, vector<char>(COLS, EMPTY));
}

// Print the board in ASCII format
void printBoard(const vector<vector<char> >& board) {
    cout << "\n 1 2 3 4 5\n";  // Column numbers (columns are numbered 1 to 7)
    for (const auto& row : board) {
        cout << "|";
        for (char cell : row) {
            cout << cell << "|";
        }
        cout << "\n";
    }
    cout << "-----------------------------\n";  // Bottom border
} 

// Place a piece at a specified row and column
bool placePiece(vector<vector<char> >& board, int row, int col, char player) {
    // Convert user input (1-indexed) to 0-indexed
    int r = row - 1;
    int c = col - 1;
    
    // Validate row and column
    if (r < 0 || r >= ROWS || c < 0 || c >= COLS) {
        cout << "Invalid coordinates! Please enter values within the board dimensions.\n";
        return false;
    }
    
    // Check if the selected cell is empty
    if (board[r][c] != EMPTY) {
        cout << "That cell is already occupied! Try a different position.\n";
        return false;
    }
    
    // Place the piece
    board[r][c] = player;
    return true;
}

// Check for a win (horizontal, vertical, diagonal)
bool checkWin(const vector<vector<char> >& board, char player) {
    // Check horizontal
    for (int r = 0; r < ROWS; ++r)
        for (int c = 0; c < COLS - 3; ++c)
            if (board[r][c] == player && board[r][c + 1] == player &&
                board[r][c + 2] == player && board[r][c + 3] == player)
                return true;

    // Check vertical
    for (int c = 0; c < COLS; ++c)
        for (int r = 0; r < ROWS - 3; ++r)
            if (board[r][c] == player && board[r + 1][c] == player &&
                board[r + 2][c] == player && board[r + 3][c] == player)
                return true;

    // Check diagonal (\ direction)
    for (int r = 0; r < ROWS - 3; ++r)
        for (int c = 0; c < COLS - 3; ++c)
            if (board[r][c] == player && board[r + 1][c + 1] == player &&
                board[r + 2][c + 2] == player && board[r + 3][c + 3] == player)
                return true;

    // Check diagonal (/ direction)
    for (int r = 3; r < ROWS; ++r)
        for (int c = 0; c < COLS - 3; ++c)
            if (board[r][c] == player && board[r - 1][c + 1] == player &&
                board[r - 2][c + 2] == player && board[r - 3][c + 3] == player)
                return true;

    return false;
}

// Check if the board is full
bool isBoardFull(const vector<vector<char> >& board) {
    for (int r = 0; r < ROWS; ++r)
        for (int c = 0; c < COLS; ++c)
            if (board[r][c] == EMPTY)
                return false;
    return true;
}

int main() {
    vector<vector<char> > board(ROWS, vector<char>(COLS, EMPTY));
    initializeBoard(board);
    char currentPlayer = PLAYER1;
    int row, col;

    printBoard(board);
    cout << "Player " << currentPlayer << ", enter row and column (e.g., 3 4): ";

    while (cin >> row >> col) {
        // Attempt to place the piece at the specified coordinates
        if (!placePiece(board, row, col, currentPlayer)) {
            printBoard(board);
            cout << "Player " << currentPlayer << ", enter row and column (e.g., 3 4): ";
            continue;
        }

        printBoard(board);

        if (checkWin(board, currentPlayer)) {
            cout << "Player " << currentPlayer << " wins!\n";
            break;
        }

        if (isBoardFull(board)) {
            cout << "It's a draw!\n";
            break;
        }

        // Switch player
        currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
        cout << "Player " << currentPlayer << ", enter row and column (e.g., 3 4): ";
    }

    return 0;
}
