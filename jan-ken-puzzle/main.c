#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "macros.h"
#include "board.h"

int main(int argc, char const *argv[]) {
    int i, j;
    int R, C;
    int cell;

    scanf("%d %d", &R, &C);
    BOARD *b = initBoard(R, C);

    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            scanf("%d", &cell);
            switch (cell) {
                case 0:
                    cell = 0;
                    break;
                case 1:
                    cell = ROCK;
                    break;
                case 2:
                    cell = SCISSORS;
                    break;
                case 3:
                    cell = PAPER;
                    break;
                default:
                    cell = 0;
                    break;
            }
            b->content[i][j] = cell;
        }
    }

    printBoard(b);

    b = deleteBoard(b);
    b = NULL;
    return 0;
}

