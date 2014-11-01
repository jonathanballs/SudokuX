CC=gcc

all: sudokux.c gamesolver.c sudokux.h
	$(CC) -o sudokux sudokux.c -lncurses