# Caroline Jesuíno Nunes da Silva - 9293925
# Felipe Scrochio Custódio - 9442688

from copy import deepcopy
import logging
import random
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

hits = 0    # number of times a success state is found

def computeHash(table, board):
    key = 0
    for i in range(len(board)):
        for j in range(len(board[i])):
            if board[i][j] != 0:
                key ^= table[i][j][board[i][j]]
    return key

def DFS(board, i, j, visited): 
    rows = len(board)
    cols = len(board[0])

    rowNbr = [-1, 1, 0, 0]
    colNbr = [0, 0, -1, +1]

    visited[i][j] = True

    # Recur for all connected neighbours 
    for k in range(4): 
        iNbr = i + rowNbr[k]
        jNbr = j + colNbr[k]
        if ((iNbr >= 0 and iNbr < rows) and (jNbr >= 0 and jNbr < cols)):
            if (not visited[iNbr][jNbr] and board[iNbr][jNbr]):
                DFS(board, iNbr, jNbr, visited)

def checkIslands(board):
        rows = len(board)
        cols = len(board[0])
        # Make a bool array to mark visited cells. 
        # Initially all cells are unvisited
        visited = [[False for j in range(cols)] for i in range(rows)] 
  
        # Initialize count as 0 and travese  
        # through the all cells of 
        # given matrix 
        count = 0
        for i in range(rows): 
            for j in range(cols): 
                # If a cell with value 1 is not visited yet,  
                # then new island found 
                if visited[i][j] == False and board[i][j]: 
                    # Visit all cells in this island
                    # and increment island count 
                    DFS(board, i, j, visited) 
                    count += 1
                    if (count > 1):
                        return False
        return True

def checkMove(current, neighbor):
    # rock
    if (current == 1):
        if neighbor in [0, 1, 3]:
            return False
        else:
            return True
    # scissors
    if (current == 2):
        if (neighbor in [0, 1, 2]):
            return False
        else:
            return True
    # paper
    if (current == 3):
        if (neighbor in [0, 2, 3]):
            return False
        else:
            return True
    # empty
    return False


def solve(cache, table, board, solutions, pieces):
    global hits
    success = False
    state_hits = 0

    # check cache (memoization)
    key = computeHash(table, board)
    if key in cache:
        if (cache[key][0]):
            cache[key][1] += 1
            hits = hits + cache[key][1]
        return cache[key]

    # check for islands
    if (not checkIslands(board)):
        cache[key] = [False, state_hits]
        return cache[key]
        
    # store solution if found
    if (pieces == 1):
        for i in range(len(board)):
            for j in range(len(board[i])):
                if (board[i][j] != 0):
                    solutions.append([i+1, j+1, board[i][j]])
                    cache[key] = [True, 1]
                    hits = hits + 1
                    return cache[key]

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
                        jump = solve(cache, table, deepcopy(board), solutions, pieces)
                        if (jump[0]):
                            success = True
                            state_hits = state_hits + 1

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
                        jump = solve(cache, table, deepcopy(board), solutions, pieces)
                        if (jump[0]):
                            success = True
                            state_hits = state_hits + 1

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
                        jump = solve(cache, table, deepcopy(board), solutions, pieces)
                        if (jump[0]):
                            success = True
                            state_hits = state_hits + 1

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
                        jump = solve(cache, table, deepcopy(board), solutions, pieces)
                        if (jump[0]):
                            success = True
                            state_hits = state_hits + 1

                        # undo jump
                        board[i][j+1] = neighbor
                        board[i][j] = current
                        pieces += 1
    
    # tried all possible jumps
    if (not success):
        cache[key] = [False, state_hits]
    else:
        cache[key] = [True, state_hits]
        hits = hits + state_hits
    return cache[key]

def main():
    # read board
    R, C = input().split()
    R = int(R)
    C = int(C)
    
    pieces = 0
    board = [x[:] for x in [[0] * int(C)] * int(R)]
    table = [[[random.randint(1,2**64 - 1) for i in range(4)]for j in range(C)] for k in range(R)]
       
    for i in range(R):
        line = input().split()
        for j in range(C):
            board[i][j] = int(line[j])
            if (board[i][j] != 0):
                pieces += 1
    
    # find all possible solutions
    solutions = []
    cache = {}
    solve(cache, table, deepcopy(board), solutions, pieces)

    # number of solutions
    print(hits)
    print(len(solutions))
    for solution in sorted(solutions):
        for value in solution:
            print(str(value), end=' ')
        print()

if __name__ == '__main__':
    main()
