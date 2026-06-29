#include <iostream>
#include <vector>

using namespace std;

// Function prototypes
void displayBoard(const vector<char>& board);
bool makeMove(vector<char>& board, int position, char player);
bool checkWin(const vector<char>& board, char player);
bool checkDraw(const vector<char>& board);
void resetBoard(vector<char>& board);

int main() {
    // Representing the 3x3 board as a flat vector of 9 elements
    // Initialized with placeholders '1' through '9' to guide the player
    vector<char> board = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char currentPlayer = 'X';
    bool gameRunning = true;

    cout << "=================================\n";
    cout << "   Welcome to C++ Tic-Tac-Toe!   \n";
    cout << "=================================\n";

    while (gameRunning) {
        displayBoard(board);
        int choice;
        
        // Prompt user input
        cout << "Player " << currentPlayer << ", enter a position (1-9): ";
        while (!(cin >> choice) || choice < 1 || choice > 9) {
            cout << "Invalid input! Please enter a number between 1 and 9: ";
            cin.clear(); // Clear error flag
            cin.ignore(10000, '\n'); // Discard buffer
        }

        // Try to place the move
        if (makeMove(board, choice, currentPlayer)) {
            // Check if the current move won the game
            if (checkWin(board, currentPlayer)) {
                displayBoard(board);
                cout << "\n Player " << currentPlayer << " wins! Congratulations! \n";
                
                // Ask to play again
                char reply;
                cout << "\nDo you want to play again? (y/n): ";
                cin >> reply;
                if (reply == 'y' || reply == 'Y') {
                    resetBoard(board);
                    currentPlayer = 'X'; // 'X' always starts
                } else {
                    gameRunning = false;
                }
            } 
            // Check if the game is a draw
            else if (checkDraw(board)) {
                displayBoard(board);
                cout << "\n It's a draw! Well played both. \n";
                
                char reply;
                cout << "\nDo you want to play again? (y/n): ";
                cin >> reply;
                if (reply == 'y' || reply == 'Y') {
                    resetBoard(board);
                    currentPlayer = 'X';
                } else {
                    gameRunning = false;
                }
            } 
            // Game is ongoing, switch players
            else {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        } else {
            cout << "That position is already taken! Try again.\n";
        }
    }

    cout << "\nThanks for playing! Goodbye.\n";
    return 0;
}

// Displays the current state of the 3x3 board
void displayBoard(const vector<char>& board) {
    cout << "\n";
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << " \n";
    cout << "---|---|---\n";
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << " \n";
    cout << "---|---|---\n";
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << " \n";
    cout << "\n";
}

// Updates the board if the move is valid
bool makeMove(vector<char>& board, int position, char player) {
    // Map 1-9 input to 0-8 vector indexing
    int index = position - 1; 
    
    // Check if slot is already occupied by 'X' or 'O'
    if (board[index] == 'X' || board[index] == 'O') {
        return false; 
    }
    
    board[index] = player;
    return true;
}

// Evaluates rows, columns, and diagonals for a win
bool checkWin(const vector<char>& board, char player) {
    // Winning combinations (indexes of the board vector)
    const int winConditions[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
        {0, 4, 8}, {2, 4, 6}             // Diagonals
    };

    for (int i = 0; i < 8; ++i) {
        if (board[winConditions[i][0]] == player &&
            board[winConditions[i][1]] == player &&
            board[winConditions[i][2]] == player) {
            return true;
        }
    }
    return false;
}

// Checks if all slots are filled without a winner
bool checkDraw(const vector<char>& board) {
    for (int i = 0; i < 9; ++i) {
        // If there's still a number left, the board isn't full
        if (board[i] != 'X' && board[i] != 'O') {
            return false;
        }
    }
    return true;
}

// Resets the board back to numerical placeholders for a new game
void resetBoard(vector<char>& board) {
    board = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
}
