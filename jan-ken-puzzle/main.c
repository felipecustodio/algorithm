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
                case 1:
                    cell = ROCK;
                    b->pieces += 1;
                    break;
                case 2:
                    cell = SCISSORS;
                    b->pieces += 1;
                    break;
                case 3:
                    cell = PAPER;
                    b->pieces += 1;
                    break;
                default:
                    cell = EMPTY;
                    break;
            }
            b->content[i][j] = cell;
        }
    }

    if (solve(b)) {
        fprintf(stderr, "Solution found!\n");
    } else {
        fprintf(stderr, "Solution NOT found!\n");
    }

    b = deleteBoard(b);
    b = NULL;
    return 0;
}

