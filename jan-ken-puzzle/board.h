#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdlib.h>

/* Bool */
#define TRUE 1
#define FALSE 0

/* Pieces */
#define ROCK 2
#define PAPER 3
#define SCISSORS 4
#define EMPTY 5

typedef struct board {
    int rows, cols;
    int pieces;
    int** content;
} BOARD;

BOARD* initBoard(int rows, int cols) {
    int i, j;
    BOARD *b = (BOARD *)malloc(sizeof(BOARD));
    b->rows = rows;
    b->cols = cols;
    b->content = (int **)malloc(sizeof(int *));
    for (i = 0; i < rows; i++) {
        b->content[i] = (int *)malloc(sizeof(int) * cols);
        for (j = 0; j < cols; j++) {
            b->content[i][j] = EMPTY;
        }
    }
    return b;
}

BOARD* deleteBoard(BOARD *b) {
    int i;
    for (i = 0; i < b->rows; i++) {
        free(b->content[i]);
    }
    free(b->content);
    free(b);
    b = NULL;
    return b;
}

void printBoard(BOARD *b, int x, int y) {
    int i, j;

    fprintf(stderr, "*");
    for (i = 0; i < b->cols; i++) {
        fprintf(stderr, "******");
    }
    fprintf(stderr, "*\n");

    for (i = 0; i < b->rows; i++) {
        fprintf(stderr, "*");
        for (j = 0; j < b->cols; j++) {
            if (i == x && j == y) {
                switch (b->content[i][j]) {
                    case ROCK:
                        fprintf(stderr, "[ R! ]");
                        break;
                    case PAPER:
                        fprintf(stderr, "[ P! ]");
                        break;
                    case SCISSORS:
                        fprintf(stderr, "[ S! ]");
                        break;
                    default:
                        fprintf(stderr, "[  ! ]");
                        break;
                }
            } else {
                switch (b->content[i][j]) {
                    case ROCK:
                        fprintf(stderr, "[ R  ]");
                        break;
                    case PAPER:
                        fprintf(stderr, "[ P  ]");
                        break;
                    case SCISSORS:
                        fprintf(stderr, "[ S  ]");
                        break;
                    default:
                        fprintf(stderr, "[    ]");
                        break;
                }
            }
        }
        fprintf(stderr, "*\n");
    }

    fprintf(stderr, "*");
    for (i = 0; i < b->cols; i++) {
        fprintf(stderr, "******");
    }
    fprintf(stderr, "*\n");
}

/* check if there's only one piece left */
char gameOver(BOARD *b) {
    if (b->pieces > 1) {
        return FALSE;
    }
    else {
        return TRUE;
    }
}

// a = current piece
// b = neighbor
char checkMove(int a, int b) {
    switch (a) {
        case ROCK:
            switch (b) {
                case ROCK:
                    return FALSE;
                    break;
                case PAPER:
                    return FALSE;
                    break;
                case SCISSORS:
                    return TRUE;
                    break;
                case EMPTY:
                    return FALSE;
                    break;
            }
            break;
        
        case PAPER:
            switch (b) {
                case ROCK:
                    return TRUE;
                    break;
                case PAPER:
                    return FALSE;
                    break;
                case SCISSORS:
                    return FALSE;
                    break;
                case EMPTY:
                    return FALSE;
                    break;
            }
            break;
        
        case SCISSORS:
            switch (b) {
                case ROCK:
                    return FALSE;
                    break;
                case PAPER:
                    return TRUE;
                    break;
                case SCISSORS:
                    return FALSE;
                    break;
                case EMPTY:
                    return FALSE;
                    break;
            }
        break;
    }
    return FALSE;
}

char solve(BOARD* b, int start_row, int start_col) {
    int i, j;
    int current, neighbor;

    fprintf(stderr, "\n** Solver entered [%d][%d]\n", start_row, start_col);
    fprintf(stderr, "\nCurrent board state:\n");
    printBoard(b, start_row, start_col);
    fprintf(stderr, "Pieces left: %d.\n", b->pieces);
    fprintf(stderr, "\n");
    
    // check if solution was found
    if (gameOver(b)) {
        return TRUE;
    }

    // check all alive pieces for possible jumps
    for (i = start_row; i < b->rows; i++) {
        for (j = start_col; j < b->cols; j++) {
            current = b->content[i][j];
            if (current != EMPTY) {
                // try all possible jumps
                printBoard(b, start_row, start_col);
                fprintf(stderr, "\nTrying all possible jumps for piece [%d][%d]\n\n", i, j);
                
                // UP
                fprintf(stderr, "Checking UP...\n");
                if (i-1 >= 0) {
                    neighbor = b->content[i-1][j];
                    if (checkMove(current, neighbor)) {
                        fprintf(stderr, "\n* Jumping UP\n");
                        // execute jump
                        b->content[i-1][j] = current;
                        b->content[i][j] = EMPTY;
                        if (neighbor != EMPTY) b->pieces -= 1;
                        // recursive call
                        if (solve(b, i-1, j) || solve(b, 0, 0)) {
                            return TRUE;
                        } else {
                            // reset the jump
                            fprintf(stderr, "Jump failed, resetting...\n\n");
                            printBoard(b, i, j);
                            b->content[i-1][j] = neighbor;
                            b->content[i][j] = current;
                            if (neighbor != EMPTY) b->pieces += 1;
                        }
                    }
                }

                // DOWN
                fprintf(stderr, "Checking DOWN...\n");
                if (i+1 < b->rows) {
                    neighbor = b->content[i+1][j];
                    if (checkMove(current, neighbor)) {
                        fprintf(stderr, "\n* Jumping DOWN\n");
                        // execute jump
                        b->content[i+1][j] = current;
                        b->content[i][j] = EMPTY;
                        if (neighbor != EMPTY) b->pieces -= 1;
            
                        // recursive call
                        if (solve(b, i+1, j) || solve(b, 0, 0)) {
                            return TRUE;
                        } else {
                            // reset the jump
                            fprintf(stderr, "Jump failed, resetting...\n\n");
                            printBoard(b, i, j);
                            b->content[i+1][j] = neighbor;
                            b->content[i][j] = current;
                            if (neighbor != EMPTY) b->pieces += 1;
                        }
                    }
                }

                // LEFT
                fprintf(stderr, "Checking LEFT...\n");
                if (j-1 >= 0) {
                    neighbor = b->content[i][j-1];
                    if (checkMove(current, neighbor)) {
                        fprintf(stderr, "\n* Jumping LEFT\n");
                        // execute jump
                        b->content[i][j-1] = current;
                        b->content[i][j] = EMPTY;
                        if (neighbor != EMPTY) b->pieces -= 1;

                        // recursive call
                        if (solve(b, i, j-1) || solve(b, 0, 0)) {
                            return TRUE;
                        } else {
                            // reset the jump
                            fprintf(stderr, "Jump failed, resetting...\n\n");
                            printBoard(b, i, j);
                            b->content[i][j-1] = neighbor;
                            b->content[i][j] = current;
                            if (neighbor != EMPTY) b->pieces += 1;
                        }
                    }
                }

                // RIGHT
                fprintf(stderr, "Checking RIGHT...\n");
                if (j+1 < b->cols) {
                    neighbor = b->content[i][j+1];
                    if (checkMove(current, neighbor)) {
                        fprintf(stderr, "\n* Jumping RIGHT\n");
                        // execute jump
                        b->content[i][j+1] = current;
                        b->content[i][j] = EMPTY;
                        if (neighbor != EMPTY) b->pieces -= 1;

                        // recursive call
                        if (solve(b, i, j+1) || solve(b, 0, 0)) {
                            return TRUE;
                        } else {
                            // reset the jump
                            fprintf(stderr, "Jump failed, resetting...\n\n");
                            printBoard(b, i, j);
                            b->content[i][j+1] = neighbor;
                            b->content[i][j] = current;
                            if (neighbor != EMPTY) b->pieces += 1;
                        }
                    }
                }
                
                // tried all possible jumps for this piece 
                fprintf(stderr, "\nThis piece can't jump anywhere nor leads to a solution. Moving on...\n\n");
            }
        }
    }
    // tried all possible jumps for current board state, no solution was found
    fprintf(stderr, "\nTried all possible movements for current alive pieces. Current state won't lead to a solution.\n");
    return FALSE;
}

BOARD* backupBoard(BOARD* b) {
    int i, j;
    BOARD* backup = initBoard(b->rows, b->cols);
    for (i = 0; i < b->rows; i++) {
        for (j = 0; j < b->cols; j++) {
            backup->content[i][j] = b->content[i][j];
        }
    }
    backup->pieces = b->pieces;
    return backup;
}

BOARD* restoreBoard(BOARD* b, BOARD* backup) {
    int i, j;
    for (i = 0; i < b->rows; i++) {
        for (j = 0; j < b->cols; j++) {
            b->content[i][j] = backup->content[i][j];
        }
    }
    b->pieces = backup->pieces;
    return b;
}

char compareState(BOARD* s1, BOARD* s2) {
    int i, j;
    for (i = 0; i < s1->rows; i++) {
        for (j = 0; j < s1->cols; j++) {
            if (s1->content[i][j] != s2->content[i][j]) {
                return FALSE;
            }
        }
    }
    return TRUE;
}

int convertPiece(int piece) {
    int converted = 1;
    switch(piece) {
        case ROCK:
            converted = 1;
            break;
        case SCISSORS:
            converted = 2;
            break;
        case PAPER:
            converted = 3;
            break;
        case EMPTY:
            converted = 0;
            break;
    }
    return converted;
}

#endif
