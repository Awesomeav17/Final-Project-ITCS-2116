

/*
 * This is a Connect4 game where two players take turns dropping discs (X's and O's)
 *  into a game board.  The first player to achieve 4 discs in a row wins.
 *  This program utilizes multiple functions, as well as concepts learned in thi
 *  class.  It checks for wins, checks for a draw, and also calculates if a input
 *  move is valid.
 */


#include <stdio.h>

//Defines two constants that will not change
#define ROWS 6
#define COLS 7

//Defines the array used for the board
char board[ROWS][COLS];

//Function that creates the board
void initialize_board() {

    //nested loop that cycles through the array, printing ' '
    for (int i = 0; i < ROWS; i++) {

        for (int j = 0; j < COLS; j++) {

            board[i][j] = ' ';

        }

    }

}

//Function that displays the current board to the user
void display_board() {

    printf("\n");

    //Nested loop that prints out the board in the current state of the game
    for (int i = 0; i < ROWS; i++) {

        printf("|");

        for (int j = 0; j < COLS; j++) {

            printf(" %c |", board[i][j]);

        }

        printf("\n");

    }

    //Prints the GUI below the board
    printf("-----------------------------\n");
    printf("| 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n");

}

//Function that puts a piece in an empty column
int drop_piece(int column, char piece) {

    //loop that checks to make sure the column is empty before placing the piece.
    for (int i = ROWS - 1; i >= 0; i--) {

        if (board[i][column] == ' ') {

            board[i][column] = piece;

            return i;

        }

    }

    return -1;  // Column is full

}

//Function that checks to see if there is a winner
int check_winner(int row, int col, char piece) {

    int count = 0;
    
    // Check horizontally
    for (int i = col - 3; i <= col + 3; i++) {

        if (i >= 0 && i + 3 < COLS) {

            count = 0;

            for (int j = 0; j < 4; j++) {

                if (board[row][i + j] == piece)

                    count++;

            }

            if (count == 4)

                return 1;

        }

    }
    
    // Check vertically
    for (int i = row - 3; i <= row + 3; i++) {

        if (i >= 0 && i + 3 < ROWS) {

            count = 0;

            for (int j = 0; j < 4; j++) {

                if (board[i + j][col] == piece)

                    count++;

            }

            if (count == 4)

                return 1;

        }

    }
    
    // Check diagonally
    for (int i = -3; i <= 3; i++) {

        if (row + i >= 0 && row + i + 3 < ROWS && col + i >= 0 && col + i + 3 < COLS) {

            count = 0;

            for (int j = 0; j < 4; j++) {

                if (board[row + i + j][col + i + j] == piece)

                    count++;

            }

            if (count == 4)

                return 1;

        }

        if (row - i >= 0 && row - i - 3 < ROWS && col + i >= 0 && col + i + 3 < COLS) {

            count = 0;

            for (int j = 0; j < 4; j++) {

                if (board[row - i - j][col + i + j] == piece)

                    count++;

            }

            if (count == 4)

                return 1;

        }

    }
    
    return 0;
}


//Main function
int main() {

    //Initializes several starting variables
    int column, row, turn = 0;
    char piece = 'X';
    
    //Calls 2 functions to begin the game
    initialize_board();
    display_board();
    
    //Loop that cycles through the game
    while (1) {

        //Asks the user to enter a column number
        printf("Player %d's turn (Choose column 1-7): ", turn % 2 + 1);
        scanf("%d", &column);
        column--;
        
        //If statement that checks to make sure the move made is valid
        if (column < 0 || column >= COLS || board[0][column] != ' ') {
            printf("Invalid move! Please choose another column.\n");
            continue;
        }
        
        //Places piece
        row = drop_piece(column, piece);

        //Displays board for the player
        display_board();
        
        //Checks for win.  If found, it breaks the loop
        if (check_winner(row, column, piece)) {
            printf("Player %d wins!\n", turn % 2 + 1);
            break;
        }
        
        //Increases the turn counter, used to track who's turn it is
        turn++;

        //Checks to see if a draw has occured.
        if (turn == ROWS * COLS) {
            printf("It's a draw!\n");
            break;
        }
        
        //Toggles between X and O pieces
        piece = (piece == 'X') ? 'O' : 'X';
    }
    
    return 0;
}
