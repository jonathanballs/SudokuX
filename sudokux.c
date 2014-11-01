// SudokuX
// Release 1.5
// Arguments: File containing Sudoku Puzzle Strings
// Output: Ascii graphic of last puzzle solved and percentSolved solved on exit
// Author: Jonathan Balls

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>

#include "sudokux.h"
#include "gamesolver.c"

main(int argc, char *argv[]) {
	int			i, j;

	// Number of puzzles solved and failed.
	int 		solved = 		0;
	int			failed = 		0;

	// Total number of problems to be solved.
	int			problemCount;

	// Percentage of puzzles solved
	float 		percentSolved;

	// Variable to hold filename of sudoku puzzles
	char		filename[MAX_FILENAME_LENGTH];
	int			currentproblem[SUDOKU_CELLS];

	// Check whether an argument has been passed and whether it contains an
	// accessible filename.
	if (!errCheck(argc, argv))
		return;

	// argv[1] is where filename should be. This needs to be updated.
	strcpy(filename, argv[1]);

	// Exit with error 1 if there aren't any problems in the file
	problemCount = getProblemCount(filename);
	if (!problemCount)
		return 1;

	// Gets all _valid_ sudoku puzzles from the file and puts them into a
	// large array.
	char problemList[problemCount][SUDOKU_CELLS];
	fileToStack(filename, problemList, problemCount);

	//initialises screen for ncurses
	initscr();//initialises screen for ncurses
	for (i=0;i<problemCount;i++) { //solves each sudoku
		printUnsolved(problemList, i, filename);
		setCurrentProblem(problemList, currentproblem, i); //takes a new problem from the list

		switch (solveSudoku(currentproblem)){
			case 1:
				solved++;
				break;
			case -1:
				failed++;
				break;
		}
		setSolvedProblem(problemList, currentproblem, i);
		printSolved(problemList, i, solved, failed, problemCount);
	}
	endwin();
	percentSolved = solved;
	percentSolved = 100 * percentSolved / problemCount;
	printf("%d(%.2f%%) solved out of %d\n", solved, percentSolved, problemCount);
	return 0;
}

setCurrentProblem(char problemList[][SUDOKU_CELLS],int currentproblem[SUDOKU_CELLS], int i) {
	int j;
	for (j=0;j<SUDOKU_CELLS;j++) {
		if (problemList[i][j] == EMPTY_CELL) {
			currentproblem[j] = 0;
		}
		else {
			currentproblem[j] = problemList[i][j] - '0';
		}
	}
}

setSolvedProblem(char problemList[][SUDOKU_CELLS], int currentproblem[SUDOKU_CELLS], int i) {
	int j;
	for (j=0;j<SUDOKU_CELLS;j++) {
		if (currentproblem[j]==0) {
			problemList[i][j]= EMPTY_CELL;
		}
		else {
			problemList[i][j]= currentproblem[j] + '0';
		}
	}
}

errCheck(int argc, char *argv[]) { //checks for errors in the arguments
	if (!(argc-1)) {
		printf("Err: Argument required\n");
		return 0;
	}
	char filename[256];
	strcpy(filename, argv[1]);
	if(access( filename, R_OK ) == -1) {
		printf("Err: File does not exists\n");
		return 0;
	}
	return 1;
}

getProblemCount(char filename[MAX_FILENAME_LENGTH]) { //accepts filename and returns linecount
	FILE *pf;
	char ch;
	int lines = 0;
	pf = fopen(filename, "r");
	ch = fgetc(pf);
	while (ch != EOF) {
		if (ch == '\n')
			lines++;
		ch = fgetc(pf);
	}
	fclose(pf);
	return lines;
}

fileToStack(char filename[MAX_FILENAME_LENGTH],char problemList[][SUDOKU_CELLS],int problemCount) {
	int i;
	FILE *pf;
	pf = fopen(filename, "r");

	for (i=0;i<problemCount;i++) {
		fgets(problemList[i], 255, pf);
  	}
	fclose(pf);
}

printUnsolved(char problemList[][SUDOKU_CELLS],int problem, char filename[256]) {
	clear();
	int i, row, col, startx;
	getmaxyx(stdscr,row,col);
	startx = col/2 - 27;
	int currenty = 2;

	mvprintw(0, (col/2) - (strlen(filename)/2), "%s", filename);//prints filename center top
	mvprintw(++currenty, startx,"+ - - - + - - - + - - - +");
	mvprintw(++currenty, startx, "| ");

  for (i=0;i<SUDOKU_CELLS;i++) {
	printw("%c ", problemList[problem][i]);
	if ((i+1)%3 == 0) {
	  if ((i+1)%9 == 0) {
		if ((i+1)%27 == 0) {
		  if ((i+1)%SUDOKU_CELLS == 0) {
			printw("|");
			mvprintw(++currenty, startx, "+ - - - + - - - + - - - +");
			move(++currenty, startx);
			continue; }
		  printw("|");
		  mvprintw(++currenty, startx, "+ - - - + - - - + - - - +");
		  mvprintw(++currenty, startx, "| ");
		  continue; }
		printw("|");
		mvprintw(++currenty, startx, "| ");
		continue; }
	  printw("| ");
	  continue; }
  }
}

printSolved(char problemList[][SUDOKU_CELLS],int problem, int solved, int failed, int problemCount) {
	int i, row, col, startx;
	getmaxyx(stdscr,row,col);
	startx = col/2 + 2;
	int currenty = 2;

	mvprintw(++currenty, startx,"+ - - - + - - - + - - - +");
	mvprintw(++currenty, startx, "| ");

	for (i=0;i<SUDOKU_CELLS;i++) {
		printw("%c ", problemList[problem][i]);
		if ((i+1)%3 == 0) {
			if ((i+1)%9 == 0) {
				if ((i+1)%27 == 0) {
					if ((i+1)%81 == 0) {
						printw("|");
						mvprintw(++currenty, startx, "+ - - - + - - - + - - - +");
						move(++currenty, startx);
						continue;
					}
				printw("|");
				mvprintw(++currenty, startx, "+ - - - + - - - + - - - +");
				mvprintw(++currenty, startx, "| ");
				continue;
				}
			printw("|");
			mvprintw(++currenty, startx, "| ");
			continue;
			}
			printw("| ");
			continue;
		}
	}

	int centre = col/2;
	mvprintw(++currenty, centre-16, "Sudoku Number:    %d", problem+1);
	mvprintw(++currenty, centre-9, "Solved:    %d", solved);
	mvprintw(++currenty, centre-9, "Failed:    %d", failed);
	mvprintw(++currenty, centre-11, "Unsolved:    %d", (problem+1)-solved);
	mvprintw(++currenty, centre-12, "Remaining:    %d", (problemCount-problem)-1);
	refresh();
}