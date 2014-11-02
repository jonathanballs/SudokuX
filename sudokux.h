//width of a sudoku puzzle
#define SUDOKU_COLUMNS				9

//number of columns of boxes (usually 3x3 areas)
#define SUDOKU_BOX_COLUMNS			3

//height of a sudoku puzzle
#define SUDOKU_ROWS					9

//number of rows of boxes
#define SUDOKU_BOX_ROWS				3

//total number of cells
#define SUDOKU_CELLS				SUDOKU_ROWS * SUDOKU_COLUMNS

//maximum length of the filename passed to the program
#define MAX_FILENAME_LENGTH			256

//character used to signify empty cell
#define EMPTY_CELL					'.'

//character height of ascii puzzle
#define ASCII_HEIGHT				14

//character width of ascii puzzle
#define ASCII_WIDTH					25

//ascii margin between top edge and puzzles
#define ASCII_TOP_MARGIN			3

//ascii margin between the solved and unsolved puzzles.
#define ASCII_CENTRE_MARGIN			4

struct coordinates
{
	int x;
	int y;
};

struct windows
{
	WINDOW *unsolved;
	WINDOW *solved;
};

struct successStatistics
{
	int solved;
	int failed;
};

void prepareterminal(char filename[MAX_FILENAME_LENGTH], struct windows* window);
int **fileTo2DArray(char filename[MAX_FILENAME_LENGTH], int *problemCount);