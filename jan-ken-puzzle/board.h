#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdlib.h>
#include "macros.h"

#define ROCK 2
#define PAPER 3
#define SCISSORS 4
#define EMPTY 5

typedef struct board {
    int rows, cols;
    int pieces;
    int** content;
} BOARD;

BOARD *initBoard(int rows, int cols)
{
    int i, j;
    BOARD *b = (BOARD *)malloc(sizeof(BOARD));
    b->rows = rows;
    b->cols = cols;
    b->content = (int **)malloc(sizeof(int *));
    for (i = 0; i < rows; i++)
    {
        b->content[i] = (int *)malloc(sizeof(int) * cols);
        for (j = 0; j < cols; j++)
        {
            b->content[i][j] = EMPTY;
        }
    }
    return b;
}

BOARD *deleteBoard(BOARD *b)
{
    int i;
    for (i = 0; i < b->rows; i++)
    {
        free(b->content[i]);
    }
    free(b->content);
    free(b);
    b = NULL;
    return b;
}

void printBoard(BOARD *b)
{
    int i, j;

    fprintf(stderr, "*");
    for (i = 0; i < b->cols; i++)
    {
        fprintf(stderr, "***");
    }
    fprintf(stderr, "*\n");

    for (i = 0; i < b->rows; i++)
    {
        fprintf(stderr, "*");
        for (j = 0; j < b->cols; j++)
        {
            switch (b->content[i][j])
            {
            case ROCK:
                fprintf(stderr, "[R]", b->content[i][j]);
                break;
            case PAPER:
                fprintf(stderr, "[P]", b->content[i][j]);
                break;
            case SCISSORS:
                fprintf(stderr, "[S]", b->content[i][j]);
                break;
            default:
                fprintf(stderr, "[ ]", b->content[i][j]);
                break;
            }
        }
        fprintf(stderr, "*\n");
    }

    fprintf(stderr, "*");
    for (i = 0; i < b->cols; i++)
    {
        fprintf(stderr, "***");
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

char checkMove(int a, int b)
{
    switch (a)
    {
    case ROCK:
        switch (b)
        {
        case ROCK:
            return FALSE;
            break;
        case PAPER:
            return FALSE;
            break;
        case SCISSORS:
            return TRUE;
            break;
        }
        break;
    case PAPER:
        switch (b)
        {
        case ROCK:
            return TRUE;
            break;
        case PAPER:
            return FALSE;
            break;
        case SCISSORS:
            return FALSE;
            break;
        }
        break;

    case SCISSORS:
        switch (b)
        {
        case ROCK:
            return FALSE;
            break;
        case PAPER:
            return TRUE;
            break;
        case SCISSORS:
            return FALSE;
            break;
        }
        break;

    default:
        return TRUE;
        break;
    }
}

// The objective of the game is to make valid moves until there is only one piece left.
// There are three valid moves:

// Move a rock piece into a neighbor cell, if the neighbor cell contains a scissors piece. The scissors piece is discarded;
// Move a scissors piece into a neighbor cell, if the neighbor cell contains a paper piece. The paper piece is discarded; and
// Move a paper piece into a neighbor cell, if the neighbor cell contains a rock piece. The rock piece is discarded.

// if there is only n = 1 piece left, return indicating we found a solution,
// otherwise, we did not;
// otherwise, for each possible jump,
// modify the board to account for the jump and call the backtracking algorithm recursively, where
// if the algorithm indicates success, record the jump and return indicating we found a solution,
// otherwise, reset the board to the state it was in prior to making the jump; and
// the loop will only finish if none of the possible jumps led to a solution, so return indicating we did not find one.

char solve(BOARD* b) {
    int i, j;
    int current, neighbor;

    printf("\nCurrent board state:\n");
    printBoard(b);
    printf("Pieces left: %d.\n", b->pieces);
    printf("\n");
    
    // check if solution was found
    if (gameOver(b)) {
        return TRUE;
    }

    // check all alive pieces for possible jumps
    for (i = 0; i < b->rows; i++) {
        for (j = 0; j < b->cols; j++) {
            current = b->content[i][j];
            if (current != EMPTY) {
                printf("Trying all possible jumps for piece [%d][%d]\n", i, j);
                // try all possible jumps
                // UP
                if (i-1 > 0) {
                    neighbor = b->content[i-1][j];
                    if (checkMove(current, neighbor))
                    {
                        printf("Jumping UP\n");
                        // execute jump
                        b->content[i-1][j] = current;
                        b->content[i][j] = EMPTY;
                        if (neighbor != EMPTY) b->pieces -= 1;
                        // recursive call
                        if (solve(b))
                        {
                            return TRUE;
                        }
                        else
                        {
                            // reset the jump
                            printf("Jump failed, resetting...\n");
                            b->content[i-1][j] = neighbor;
                            b->content[i][j] = current;
                            if (neighbor != EMPTY) b->pieces += 1;
                        }
                    }
                }

                // DOWN
                if (i+1 < b->rows) {
                    neighbor = b->content[i + 1][j];
                    if (checkMove(current, neighbor))
                    {
                        printf("Jumping DOWN\n");
                        // execute jump
                        b->content[i + 1][j] = current;
                        b->content[i][j] = EMPTY;
                        if (neighbor != EMPTY) b->pieces -= 1;
            
                        // recursive call
                        if (solve(b))
                        {
                            return TRUE;
                        }
                        else
                        {
                            // reset the jump
                            printf("Jump failed, resetting...\n");
                            b->content[i + 1][j] = neighbor;
                            b->content[i][j] = current;
                            if (neighbor != EMPTY) b->pieces += 1;
                        }
                    }
                }

                // LEFT
                if (j-1 > 0) {
                    neighbor = b->content[i][j - 1];
                    if (checkMove(current, neighbor))
                    {
                        printf("Jumping LEFT\n");
                        // execute jump
                        b->content[i][j - 1] = current;
                        b->content[i][j] = EMPTY;
                        if (neighbor != EMPTY) b->pieces -= 1;

                        // recursive call
                        if (solve(b))
                        {
                            return TRUE;
                        }
                        else
                        {
                            // reset the jump
                            printf("Jump failed, resetting...\n");
                            b->content[i][j - 1] = neighbor;
                            b->content[i][j] = current;
                            if (neighbor != EMPTY) b->pieces += 1;
                        }
                    }
                }
                
                // RIGHT
                if (j+1 < b->cols) {
                    neighbor = b->content[i][j + 1];
                    if (checkMove(current, neighbor))
                    {
                        printf("Jumping RIGHT\n");
                        // execute jump
                        b->content[i][j + 1] = current;
                        b->content[i][j] = EMPTY;
                        if (neighbor != EMPTY) b->pieces -= 1;

                        // recursive call
                        if (solve(b))
                        {
                            return TRUE;
                        }
                        else
                        {
                            // reset the jump
                            printf("Jump failed, resetting...\n");
                            b->content[i][j + 1] = neighbor;
                            b->content[i][j] = current;
                            if (neighbor != EMPTY) b->pieces += 1;
                        }
                    }
                }
                // tried all possible jumps for this piece 
                printf("This piece can't jump anywhere. Moving on...\n");
            }
        }
    }
    // tried all possible jumps for current board state, no solution was found
    return FALSE;
}


#endif
