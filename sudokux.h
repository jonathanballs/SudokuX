//version number
#define	SUDOKUX_VERSION_NUMBER		1.5

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

//maximum length of the filename passed to the program.
#define MAX_FILENAME_LENGTH			256

//character used to signify empty cell.
#define EMPTY_CELL					'.'

//character height of ascii puzzle.
#define ASCII_HEIGHT				14

//character width of ascii puzzle.
#define ASCII_WIDTH					25

//ascii margin between top edge and puzzles.
#define ASCII_TOP_MARGIN			3

//ascii margin between the solved and unsolved puzzles.
#define ASCII_CENTRE_MARGIN			4

//number of different stats given.
#define NUMBER_OF_STATISTICS		5

//max width for a statistic. will be truncated after this.
#define STATISTICS_WIDTH			40

/*
** SETTINGS FLAGS
*/

// silent mode: turns off curses
#define FLAGS_SILENT_MODE				'-s'

// help message
#define FLAGS_HELP_MESSAGE				'-h'

/*
** DEFAULT SETTINGS
*/

// curses mode
#define DEFAULT_CURSES_MODE				true
// These coordinates are used at various points when dealing with ncurses.
struct coordinates
{
	int x;
	int y;
};

// These windows are all sub-areas of the main sdtscr in ncurses. Their
// functions whould be fairly self explanatory.
struct windows
{
	WINDOW *unsolved;
	WINDOW *solved;
	WINDOW *statistics;
};

struct settings {
	bool cursesMode;
};

// sudokux.c
void prepareterminal(char filename[MAX_FILENAME_LENGTH], struct windows* window);
int **fileTo2DArray(char filename[MAX_FILENAME_LENGTH], int *problemCount);
void displayPuzzle(WINDOW *puzzleWin, int sudokupuzzle[SUDOKU_CELLS]);
void updateStatistics(int attempts, int solved, int problemCount, WINDOW *statistics);
void printVersionNumber();