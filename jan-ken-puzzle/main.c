// Caroline Jesuíno Nunes da Silva - 9293925
// Felipe Scrochio Custódio - 9442688

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

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
    b->pieces = 0;
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

BOARD *backupBoard(BOARD *b) {
    int i, j;
    BOARD *backup = initBoard(b->rows, b->cols);
    for (i = 0; i < b->rows; i++) {
        for (j = 0; j < b->cols; j++) {
            backup->content[i][j] = b->content[i][j];
        }
    }
    backup->pieces = b->pieces;
    return backup;
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

char solve(BOARD* b, BOARD*** solutions, int* n_solutions) {
    int i, j, k;
    int current, neighbor;

    // check if solution was found
    if (gameOver(b)) {
        (*solutions) = (BOARD**)realloc((*solutions), sizeof(BOARD*) * (*n_solutions) + 1);
        (*solutions)[(*n_solutions)] = backupBoard(b);
        (*n_solutions) = (*n_solutions) + 1;
        return TRUE;
    }

    // check all alive pieces for possible jumps
    for (i = 0; i < b->rows; i++) {
        for (j = 0; j < b->cols; j++) {
            current = b->content[i][j];

            if (current != EMPTY) {
                
                // UP
                if (i-1 >= 0) {
                    neighbor = b->content[i-1][j];
                    if (checkMove(current, neighbor)) {
                        
                        // execute jump
                        fprintf(stderr, "[JUMP] %d,%d to %d,%d\n", i,j,i-1,j);
                        
                        b->content[i-1][j] = current;
                        b->content[i][j] = EMPTY;
                        if (neighbor != EMPTY) b->pieces -= 1;
                        
                        // recursive call
                        solve(b, solutions, n_solutions);
                       
                        // reset the jump
                        b->content[i-1][j] = neighbor;
                        b->content[i][j] = current;
                        if (neighbor != EMPTY) b->pieces += 1;
                    }
                }

                // DOWN
                if (i+1 < b->rows) {
                    neighbor = b->content[i+1][j];
                    if (checkMove(current, neighbor)) {
                        
                        // execute jump
                        //fprintf(stderr, "[JUMP] %d,%d to %d,%d\n", i,j,i+1,j);

                        b->content[i+1][j] = current;
                        b->content[i][j] = EMPTY;
                        if (neighbor != EMPTY) b->pieces -= 1;
            
                        // recursive call
                        solve(b, solutions, n_solutions);
                        
                        // reset the jump
                        b->content[i+1][j] = neighbor;
                        b->content[i][j] = current;
                        if (neighbor != EMPTY) b->pieces += 1;
                    }
                }

                // LEFT
                if (j-1 >= 0) {
                    neighbor = b->content[i][j-1];
                    if (checkMove(current, neighbor)) {
                        
                        // execute jump
                        //fprintf(stderr, "[JUMP] %d,%d to %d,%d\n", i,j,i,j-1);

                        b->content[i][j-1] = current;
                        b->content[i][j] = EMPTY;
                        if (neighbor != EMPTY) b->pieces -= 1;

                        // recursive call
                        solve(b, solutions, n_solutions);

                        // reset the jump
                        b->content[i][j-1] = neighbor;
                        b->content[i][j] = current;
                        if (neighbor != EMPTY) b->pieces += 1;
                    }
                }

                // RIGHT
                if (j+1 < b->cols) {
                    neighbor = b->content[i][j+1];
                    if (checkMove(current, neighbor)) {

                        // execute jump
                        //fprintf(stderr, "[JUMP] %d,%d to %d,%d\n", i,j,i,j+1);

                        b->content[i][j+1] = current;
                        b->content[i][j] = EMPTY;
                        if (neighbor != EMPTY) b->pieces -= 1;

                        // recursive call
                        solve(b, solutions, n_solutions);

                        // reset the jump
                        b->content[i][j + 1] = neighbor;
                        b->content[i][j] = current;
                        if (neighbor != EMPTY) b->pieces += 1;
                    }
                }
            }
        }
    }
    return FALSE;
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

int main(int argc, char const *argv[]) {
    // board input
    int R, C;
    int cell;

    // helpers
    int i, j;
    char buffer[64];
    int bytes; 

    clock_t start_t, end_t;
    float delta_t = 0.0;

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

    fprintf(stderr, "\n[*] Starting solver...\n\n");
    start_t = clock();

    // check for all possible solutions
    solve(b, &solutions, &n_solutions);

    end_t = clock();
    delta_t = ((float)(end_t - start_t) / 1000000000000.0F) * CLOCKS_PER_SEC;
    fprintf(stderr, "\n[!] Solver finished - %lfs\n\n", delta_t);

    if (n_solutions <= 0) {
        fprintf(stderr, "[!] No solutions found.\n");
        exit(0);
    }

    // count distinct solutions
    unique_solutions = (BOARD**)malloc(sizeof(BOARD*) * n_solutions);
    final_states = (int*)malloc(sizeof(int) * n_solutions);

    unique_solutions[0] = backupBoard(solutions[0]);

    // store final board state as integer (row, column, piece)
    for (i = 0; i < unique_solutions[0]->rows; i++) {
        for (j = 0; j < unique_solutions[0]->cols; j++) {
            if (unique_solutions[0]->content[i][j] != EMPTY) {
                fprintf(stderr, "[SOLUTION]\n");
                printBoard(unique_solutions[0], i, j);
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
                        fprintf(stderr, "[SOLUTION]\n");
                        printBoard(unique_solutions[n_unique_solutions], i, j);
                        final_states[n_unique_solutions] =  100 * (i+1) + 10 * (j+1) + convertPiece(unique_solutions[n_unique_solutions]->content[i][j]);
                    }
                }
            }
            n_unique_solutions++;
        }
    }

    fprintf(stderr, "\n[*] Number of ways to get to a solution: %d\n", n_solutions);
    fprintf(stderr, "[*] Number of distinct final states (solutions): %d\n\n", n_unique_solutions);

    printf("%d\n", n_solutions);
    printf("%d\n", n_unique_solutions);
    
    // sort unique final states (insertion sort)
    // fast for really small sets
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

    // store state in a buffer so it can be printed correctly (spaces between values)
    for (i = 0; i < n_unique_solutions; i++) {
        bytes = snprintf(buffer, sizeof(buffer), "%d", final_states[i]);
        for (j = 0; j < bytes; j++) {
            printf("%c ", buffer[j]);
        }
        printf("\n");
    }

    // b = deleteBoard(b);
    // b = NULL;
    return 0;
}

