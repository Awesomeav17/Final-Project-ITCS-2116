/*
Connect Four Game Project

This project implements a simple Connect Four game in C programming language. 
Players take turns dropping colored discs into a vertically suspended grid. 
The objective is to connect four of one's own discs of the same color 
next to each other vertically, horizontally, or diagonally before the opponent 
while also preventing the opponent from achieving the same goal. 

By: Avnish Ozarkar 
Class: ITCS-2116 C Programming
Date: 03/01/2024 
*/


#include <stdio.h>
#include <stdbool.h>

#define ROWS 6
#define COLS 7

char board[ROWS][COLS];

// This function initializes the game board by setting each cell to contain a space character (' ').
// It iterates through each row and column of the board, assigning the space character to each cell.
void initializeBoard() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = ' ';
        }
    }
}
// This function prints the current state of the game board to the console.
// It iterates through each cell of the board, printing the corresponding value
// (either 'X', 'O', or ' ') surrounded by '|' characters to represent the grid.
// After printing each row, it adds a horizontal line to separate rows.
// Additionally, it prints the column numbers below the board for player reference.
void printBoard() {
    printf("\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("| %c ", board[i][j]);
        }
        printf("|\n");
    }
    printf("-----------------------------\n");
    for (int j = 0; j < COLS; j++) {
        printf("  %d ", j);
    }
    printf("\n");
}

bool isWin(char player) {
    // Check horizontally
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j <= COLS - 4; j++) {
            if (board[i][j] == player && board[i][j+1] == player &&
                board[i][j+2] == player && board[i][j+3] == player) {
                return true;
            }
        }
    }

    // Check vertically
    for (int i = 0; i <= ROWS - 4; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == player && board[i+1][j] == player &&
                board[i+2][j] == player && board[i+3][j] == player) {
                return true;
            }
        }
    }

    // Check diagonally (top-left to bottom-right)
    for (int i = 0; i <= ROWS - 4; i++) {
        for (int j = 0; j <= COLS - 4; j++) {
            if (board[i][j] == player && board[i+1][j+1] == player &&
                board[i+2][j+2] == player && board[i+3][j+3] == player) {
                return true;
            }
        }
    }

    // Check diagonally (top-right to bottom-left)
    for (int i = 0; i <= ROWS - 4; i++) {
        for (int j = 3; j < COLS; j++) {
            if (board[i][j] == player && board[i+1][j-1] == player &&
                board[i+2][j-2] == player && board[i+3][j-3] == player) {
                return true;
            }
        }
    }

    return false;
}


//congratulating the winner in the output.txt message telling them they won. 
void congratulateWinner(char player) {
    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(outputFile, "Congratulations Player %c! You won the game.\n", player);
    fclose(outputFile);
}

//// This function contains the main logic for playing a simple Connect Four game,
// including initializing the game board, taking turns for players 'X' and 'O',
// checking for a win condition, and ending the game when a player wins.
int main() {
    initializeBoard();
    char currentPlayer = 'X';
    int moves = 0;

    while (true) {
        printBoard();
        int column;
        printf("Player %c, enter column number (0-6): ", currentPlayer);
        scanf("%d", &column);

        if (column < 0 || column >= COLS) {
            printf("Invalid column number. Try again.\n");
            continue;
        }
        // This loop iterates through the rows in the selected column of the game board,
        // finding the lowest empty cell to drop the current player's piece. It then checks
        // if this move results in a win for the current player. If so, it prints the updated
        // game board, congratulates the winner, and exits the game. If the column is full,
        // it informs the player to try again.
        for (int i = ROWS - 1; i >= 0; i--) {
            if (board[i][column] == ' ') {
                board[i][column] = currentPlayer;
                moves++;

                if (isWin(currentPlayer)) {
                    printBoard();
                    congratulateWinner(currentPlayer);
                    return 0;
                }

                break;
            }
            if (i == 0) {
                printf("Column full. Try again.\n");
            }
        }
        // This section of code switches the current player after each turn and checks for
        // a draw if the maximum number of moves (equal to the total number of cells in the
        // game board) is reached.
        if (currentPlayer == 'X') {
            currentPlayer = 'O';
        } else {
            currentPlayer = 'X';
        }

        if (moves == ROWS * COLS) {
            printf("It's a draw!\n");
            break;
        }
    }

    return 0;
}
