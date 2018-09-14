#!/bin/python3

import math
import os
import random
import re
import sys

solutions = 0

def powerSum(X, N, S, i):
    result = sum(map(lambda x:pow(x, N),S))
    limit = int(math.sqrt(X)) + 1

    if (result == X):
        global solutions
        solutions = solutions + 1

    for k in range(i, limit):
        if (result + pow(k, N) > X):
            break
        S.append(k)
        powerSum(X, N, S, k+1)
        S.remove(k)

if __name__ == '__main__':
    # fptr = open(os.environ['OUTPUT_PATH'], 'w')

    X = int(input())
    N = int(input())

    powerSum(X, N, [], 1)
    print(solutions)

    # fptr.write(str(solutions) + '\n')
    # fptr.close()
