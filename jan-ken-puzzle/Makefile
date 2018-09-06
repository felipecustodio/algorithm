# compiler
CC = gcc

# output
BINARY = ./puzzle

# sources directory
SRC = ./main.c

# includes directory
INCLUDES = .

# compiler flags
FLAGS = -g -std=c99 -O3

all: compile

compile:
	$(CC) -o $(BINARY) -I $(INCLUDES) $(SRC) $(FLAGS)

run:
	$(BINARY)

debug:
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes $(BINARY)

clean:
	rm *.o
