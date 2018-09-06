#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "board.h"

int main(int argc, char const *argv[]) {
    // board input
    int R, C;
    int cell;

    // helpers
    int i, j;
    char buffer[64];
    int bytes; 

    // read board from STDIN
    scanf("%d %d", &R, &C);
    
    BOARD* b = initBoard(R, C);
    BOARD* backup = initBoard(R, C);
    
    BOARD** solutions = NULL;
    BOARD** unique_solutions = NULL;
    int* final_states = NULL;

    int n_solutions = 0;
    int n_unique_solutions = 0;
    char is_unique = TRUE;

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
    backup = backupBoard(b);

    // check for all possible solutions
    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            if (b->content[i][j] != EMPTY) {
                fprintf(stderr, "\n\n***** Searching for solution starting at [%d][%d] ***** \n", i, j);
                if (solve(b, i, j)) {
                    fprintf(stderr, "********** SOLUTION FOUND!\n");
                    solutions = (BOARD**)realloc(solutions, sizeof(BOARD*) * n_solutions + 1);
                    solutions[n_solutions] = backupBoard(b);
                    n_solutions++; 
                } else {
                    fprintf(stderr, "\n********** Solution NOT found!\n");
                }
            }
            // restore board
            b = restoreBoard(b, backup);
        }
    }

    // count unique solutions
    unique_solutions = (BOARD**)malloc(sizeof(BOARD*) * n_solutions);
    final_states = (int*)malloc(sizeof(int) * n_solutions);

    unique_solutions[0] = backupBoard(solutions[0]);

    for (i = 0; i < unique_solutions[0]->rows; i++) {
        for (j = 0; j < unique_solutions[0]->cols; j++) {
            if (unique_solutions[0]->content[i][j] != EMPTY) {
                final_states[0] =  100 * (i+1) + 10 * (j+1) + convertPiece(unique_solutions[0]->content[i][j]);
            }
        }
    }

    n_unique_solutions = 1;

    for (i = 0; i <= n_solutions-1; i++) {
        is_unique = TRUE;
        for (j = 0; j < n_unique_solutions; j++) {
            if (compareState(solutions[i], unique_solutions[j])) {
                is_unique = FALSE;
            }
        }
        if (is_unique) {
            // store unique solution
            unique_solutions[n_unique_solutions] = backupBoard(solutions[i]);

            // store final state as an integer (row, column, piece)
            for (i = 0; i < unique_solutions[n_unique_solutions]->rows; i++) {
                for (j = 0; j < unique_solutions[n_unique_solutions]->cols; j++) {
                    if (unique_solutions[n_unique_solutions]->content[i][j] != EMPTY) {
                        final_states[n_unique_solutions] =  100 * (i+1) + 10 * (j+1) + convertPiece(unique_solutions[n_unique_solutions]->content[i][j]);
                    }
                }
            }
            n_unique_solutions++;
        }
    }

    fprintf(stderr, "\nNumber of ways to get to a solution: %d\n", n_solutions);
    fprintf(stderr, "Number of distinct final states (solutions): %d\n\n", n_unique_solutions);

    printf("%d\n", n_solutions);
    printf("%d\n", n_unique_solutions);
    
    // sort unique final states
    int tmp;
    for (i = 1 ; i <= n_unique_solutions - 1; i++) {
        j = i;
        while (j > 0 && final_states[j-1] > final_states[j]) {
            tmp = final_states[j];
            final_states[j] = final_states[j-1];
            final_states[j-1] = tmp;
            j--;
        }
    }

    // store state in a buffer so it can be printed correctly
    for (i = 0; i < n_unique_solutions; i++) {
        bytes = snprintf(buffer, sizeof(buffer), "%d", final_states[i]);
        for (j = 0; j < bytes; j++) {
            printf("%c ", buffer[j]);
        }
        printf("\n");
    }

    b = deleteBoard(b);
    b = NULL;
    return 0;
}

