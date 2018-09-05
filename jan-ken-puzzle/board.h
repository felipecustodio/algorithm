#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdlib.h>
#include "macros.h"

#define ROCK 2
#define PAPER 3
#define SCISSORS 4

typedef struct board {
    int rows, cols;
    int** content;
} BOARD;



char a_vs_b(int a, int b) {
    switch (a) {
        case ROCK:
            switch(b) {
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
            }
            break;
    }

}


BOARD* initBoard(int rows, int cols) {
    int i, j;
    BOARD* b = (BOARD*)malloc(sizeof(BOARD));
    b->rows = rows;
    b->cols = cols;
    b->content = (int**)malloc(sizeof(int*));
    for (i = 0; i < rows; i++) {
        b->content[i] = (int*)malloc(sizeof(int) * cols);
        for (j = 0; j < cols; j++) {
            b->content[i][j] = 0;
        }
    }
    return b;
}

BOARD* deleteBoard(BOARD* b) {
    int i;
    for (i = 0; i < b->rows; i++) {
        free(b->content[i]);
    }
    free(b->content);
    free(b);
    b = NULL;
    return b;
}

void printBoard(BOARD* b) {
    int i, j;

    fprintf(stderr, "*");
    for (i = 0; i < b->cols; i++) {
        fprintf(stderr, "***");
    }
    fprintf(stderr, "*\n");

    for (i = 0; i < b->rows; i++) {
        fprintf(stderr, "*");
        for (j = 0; j < b->cols; j++) {
            switch (b->content[i][j]) {
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
    for (i = 0; i < b->cols; i++) {
        fprintf(stderr, "***");
    }
    fprintf(stderr, "*\n");
}

#endif
