//width of a sudoku puzzle.
#define SUDOKU_COLUMNS				9

//number of columns of boxes (usually 3x3 areas).
#define SUDOKU_BOX_COLUMNS			3

//height of a sudoku puzzle.
#define SUDOKU_ROWS					9

//number of rows of boxes.
#define SUDOKU_BOX_ROWS				3

//total number of cells.
#define SUDOKU_CELLS				SUDOKU_ROWS * SUDOKU_COLUMNS

//number of cells in a box
#define SUDOKU_BOX_CELLS			9

//used for crosshatching
#define UNFOUND						-2
#define REFOUND						-1

// Used to handle gamesolver.c return values instead of relying on ints.
enum status {
	SOLVED,
	INCOMPLETE,
	FAILED
};

// gamesolver.c
enum status solveSudoku(int sudokuGrid[SUDOKU_CELLS]);
enum status constraintSearch(int sudokuGrid[SUDOKU_CELLS]);
enum status puzzleStatus(int sudokuGrid[SUDOKU_CELLS]);
bool oneLegal(int sudokuGrid[SUDOKU_CELLS]);
bool isLegal(int cell, int possibility, int sudokuGrid[SUDOKU_CELLS]);
bool crossHatch(int sudokuGrid[SUDOKU_CELLS], int (*groupMember)(int, int));
bool crossHatcher(int sudokuGrid[SUDOKU_CELLS]);
int columnCell(int column, int member);
int rowCell(int row, int member);
int boxCell(int box, int member);