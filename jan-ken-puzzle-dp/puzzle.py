# Caroline Jesuíno Nunes da Silva - 9293925
# Felipe Scrochio Custódio - 9442688
from copy import deepcopy

def checkMove(current, neighbor):
    # rock
    if (current == 1):
        # empty
        if (neighbor == 0):
            return False
        # rock
        if (neighbor == 1):
            return False
        # scissors
        if (neighbor == 2):
            return True
        # paper
        if (neighbor == 3):
            return False
    
    # scissors
    if (current == 2):
        # empty
        if (neighbor == 0):
            return False
        # rock
        if (neighbor == 1):
            return False
        # scissors
        if (neighbor == 2):
            return False
        # paper
        if (neighbor == 3):
            return True

    # paper
    if (current == 3):
        # empty
        if (neighbor == 0):
            return False
        # rock
        if (neighbor == 1):
            return True
        # scissors
        if (neighbor == 2):
            return False
        # paper
        if (neighbor == 3):
            return False
    # empty
    return False


def solve(board, solutions, pieces):
    # store solution if found
    if (pieces == 1):
        for i in range(len(board)):
            for j in range(len(board[i])):
                if (board[i][j] != 0):
                    solutions.append([i+1, j+1, board[i][j]])

    # check all alive pieces for possible jumps
    for i in range(len(board)):
        for j in range(len(board[i])):
            current = board[i][j]
            # if current is not empty
            if (current != 0):
                # UP
                if (i-1 >= 0):
                    neighbor = board[i-1][j]
                    if (checkMove(current, neighbor)):
                        # execute jump
                        board[i-1][j] = current
                        board[i][j] = 0
                        pieces -= 1
                        
                        # recursive call
                        solve(deepcopy(board), solutions, pieces)

                        # undo jump
                        board[i-1][j] = neighbor
                        board[i][j] = current
                        pieces += 1

                 # DOWN
                if (i+1 < len(board)):
                    neighbor = board[i+1][j]
                    if (checkMove(current, neighbor)):
                        # execute jump
                        board[i+1][j] = current
                        board[i][j] = 0
                        pieces -= 1
                        
                        # recursive call
                        solve(deepcopy(board), solutions, pieces)

                        # undo jump
                        board[i+1][j] = neighbor
                        board[i][j] = current
                        pieces += 1
                
                 # LEFT
                if (j-1 >= 0):
                    neighbor = board[i][j-1]
                    if (checkMove(current, neighbor)):
                        # execute jump
                        board[i][j-1] = current
                        board[i][j] = 0
                        pieces -= 1
                        
                        # recursive call
                        solve(deepcopy(board), solutions, pieces)

                        # undo jump
                        board[i][j-1] = neighbor
                        board[i][j] = current
                        pieces += 1

                 # RIGHT
                if (j+1 < len(board[i])):
                    neighbor = board[i][j+1]
                    if (checkMove(current, neighbor)):
                        # execute jump
                        board[i][j+1] = current
                        board[i][j] = 0
                        pieces -= 1
                        
                        # recursive call
                        solve(deepcopy(board), solutions, pieces)

                        # undo jump
                        board[i][j+1] = neighbor
                        board[i][j] = current
                        pieces += 1

def main():
    # read board
    R, C = input().split()
    R = int(R)
    C = int(C)
    pieces = 0
    board = [x[:] for x in [[0] * int(C)] * int(R)]

    for i in range(R):
        line = input().split()
        for j in range(C):
            board[i][j] = int(line[j])
            if (board[i][j] != 0):
                pieces += 1

    # find all possible solutions
    solutions = []
    solve(deepcopy(board), solutions, pieces)

    # number of solutions
    print(len(solutions))
    uniques = sorted(set(tuple(solution) for solution in solutions))
    print(len(uniques))
    for solution in uniques:
        for value in solution:
            print(str(value), end=' ')
        print()

if __name__ == '__main__':
    main()