// SudokuX
// Release 1.5
// Arguments: File containing Sudoku Puzzle Strings
// Output: Ascii graphic of last puzzle solved and percentage solved on exit
// (C) Jonathan Balls 2013


// This part of the code is fairly hard to follow if you don't know what's
// going on because it relies heavily on recursion. Start at the top and
// then follow the program's logic.
/*

                  +--------------------------+                                 
                  |Incomplete sudoku puzzle  |                                 
                  |is passed to solveSudoku()|                                 
                  |function.                 |                                 
                  +------------+-------------+                                 
                               |                  +-----------------------+    
                               |                  |Return failed puzzle.  |    
                               |                  +-----------^-----------+    
                  +------------v-------------+                |                
                  |Pass the incomplete puzzle|                |no              
                  |to the oneLegal() function|    +-----------+-----------+    
                  |which will fill in all the| yes|Are there any more     |    
                  |cells with only one       |  +-+possible values for the|    
                  |possible value.           |  | |cell?                  |    
                  +---------+--+-------------+  | +-----------^-----------+    
                               |                |             |no              
                               |                | +-----------+-----------+    
  +----------+                 |                | |Has it been returned   | yes
  |Return the| no +------------v-------------+  | |solved?                +---+
+->solved    <----+Are there any empty cells?|  | +-----------^-----------+   |
| |puzzle.   |    +------------+-------------+  |             |               |
| +----------+                 |                | +-----------+------------+  |
|                              |yes             | |constraintSearch() will |  |
|                              |                +->create a copy of the    |  |
| +----------+     +-----------v-------------+    |original puzzle with the|  |
| |Return the|  no |Does the first empty cell|    |possible value inserted.|  |
| |failed    <-----+you try have at least one+---->This is then sent to    |  |
| |puzzle.   |     |possible value?          |    |solveSudoku().          |  |
| +----------+     +-------------------------+    +------------------------+  |
|                                                                             |
|                                                                             |
+-----------------------------------------------------------------------------+

*/

#include <stdbool.h>

// The main function accepts a puzzle array as an argument and uses other
// functions to solve them. The array is modified directly so there is no need
// to return it at the end of the function.
enum status solveSudoku(int sudokuGrid[SUDOKU_CELLS]) {
	
	// These two functions will fill in cells which only have one posssible
	// value. They will continue passing over the puzzle until neither are able
	// to fill in any more.
	while (oneLegal(sudokuGrid) || crossHatching(sudokuGrid)) {
		;
	}

	switch(puzzleStatus(sudokuGrid)) {
		case SOLVED:
			return SOLVED;
		case FAILED:
			return FAILED;
		case INCOMPLETE:
			return constraintSearch(sudokuGrid);
	}
}

// Trial & Error.
enum status constraintSearch(int sudokuGrid[SUDOKU_CELLS]) { //
	int altcell;
	int altgrid[SUDOKU_CELLS];
	int i;

	// Find the first empty cell in the sudoku puzzle
	for (i=0;i<SUDOKU_CELLS;i++) {
		if (!sudokuGrid[i]) {
			altcell = i;
			break;
		}
	}

	// Find the first possible number that could go into that cell and try to
	// solve the puzzle with that. The guess will be wrong if the puzzle comes
	// back failed and so a new guess will be tried in the same cell. This
	// continues until the puzzle comes back solved or 
	for (i=1;i<=SUDOKU_BOX_CELLS;i++) {
		setGrid(sudokuGrid, altgrid);

		//find a possibility in that cell
		if (isLegal(altcell, i, sudokuGrid)) {

			//set that possibility to the empty cell
			altgrid[altcell] = i;

			switch (solveSudoku(altgrid)) {
				case FAILED:
					continue;
				case SOLVED:
					setGrid(altgrid, sudokuGrid);
					return SOLVED;
			}
		}
	}
	return FAILED;
}


// Passes over the sudoku puzzle and finds cells which only have one possible
// legal value and then fills in said cell with said value.
bool oneLegal(int sudokuGrid[SUDOKU_CELLS]) {
	int cell, i , j;
	int result = 0;

	// For each cell in the sudoku puzzle
	for (cell=0;cell<SUDOKU_CELLS;cell++) {

		// If the cell already has a value: skip it.
		if (sudokuGrid[cell]) {
			continue;
		}

		// Try each possible value for empty cells.
		for (i=1;i<=SUDOKU_BOX_CELLS;i++) {
			if (isLegal(cell, i, sudokuGrid)) {

				// A value will have been set already if this is not the first
				// possible value and so you can safely reset the cell and
				// continue the search.
				if (sudokuGrid[cell]) {
					result = false;
					sudokuGrid[cell] = 0;
					break;
				}

				// If this is the first possible value that is found, the cell
				// will be set accordingly.
				else {
					sudokuGrid[cell] = i;
					result = true;
				}
			}
		}
	}
	return result;
}

// Crosshatching is one of the more advanced techniques used. It passes
// through groups of cells (boxes, rows, columns) and finds if there are any
// cells which are the only one in the group to have a number as a possibility.
//
// i.e. If there is only one cell in a box which can contain the number '6',
// that cell must be '6' even if the cell has other legal possibilities.
crossHatching(int sudokuGrid[SUDOKU_CELLS]) {
	int member, group, poss, i, n;
	int result = 0;
	for (group=0; group<SUDOKU_ROWS; group++) {
		for (poss=1;poss<=SUDOKU_BOX_CELLS;poss++) {
			n=0;
			for (member=0;member<SUDOKU_BOX_CELLS;member++) {
				if(!sudokuGrid[rowCell(group, member)] && isLegal(rowCell(group, member), poss, sudokuGrid)) { //if empty and poss is legal then increase n
					++n;
				}
			}
			if (n==1) { //if there is only one possibility
				for (member=0;member<SUDOKU_BOX_CELLS;member++) {
					if(!sudokuGrid[rowCell(group, member)] && isLegal(rowCell(group, member), poss, sudokuGrid)) {
						sudokuGrid[rowCell(group, member)] = poss;
						result = 1;
						break;
					}
				}
			}
		}
	}
	for (group=0; group<SUDOKU_COLUMNS; group++) {
		for (poss=1;poss<=SUDOKU_BOX_CELLS;poss++) {
			n=0;
			for (member=0;member<SUDOKU_BOX_CELLS;member++) {
				if(!sudokuGrid[columnCell(group, member)] && isLegal(columnCell(group, member), poss, sudokuGrid)) { //if empty and poss is legal then increase n
					++n;
				}
			}
			if (n==1) { //if there is only one possibility
				for (member=0;member<SUDOKU_BOX_CELLS;member++) {
					if(!sudokuGrid[columnCell(group, member)] && isLegal(columnCell(group, member), poss, sudokuGrid)) {
						sudokuGrid[columnCell(group, member)] = poss;
						result = 1;
						break;
					}
				}
			}
		}
	}
	for (group=0; group<SUDOKU_BOX_CELLS; group++) {
		for (poss=1;poss<=SUDOKU_BOX_CELLS;poss++) {
			n=0;
			for (member=0;member<SUDOKU_BOX_CELLS;member++) {
				if(!sudokuGrid[boxCell(group, member)] && isLegal(boxCell(group, member), poss, sudokuGrid)) { //if empty and poss is legal then increase n
					++n;
				}
			}
			if (n==1) { //if there is only one possibility
				for (member=0;member<SUDOKU_BOX_CELLS;member++) {
					if(!sudokuGrid[boxCell(group, member)] && isLegal(boxCell(group, member), poss, sudokuGrid)) {
						sudokuGrid[boxCell(group, member)] = poss;
						result = 1;
						break;
					}
				}
			}
		}
	}
	return result;
}

// Duplicates a sudoku puzzle array.
setGrid(int from[SUDOKU_CELLS], int to[SUDOKU_CELLS]) {
	int i;
	for (i=0;i<SUDOKU_CELLS;i++) {
		to[i] = from[i];
	}
	return 0;
}

// Tests if a possible value is legal in the puzzle.
bool isLegal(int cell, int possibility, int sudokuGrid[SUDOKU_CELLS]) {
	int i;
	int column = cellColumn(cell);
	int row = cellRow(cell);
	int box = cellBox(cell);

	// Test if it clashes with cells in the same column
	for (i=0;i<SUDOKU_COLUMNS;i++) {
		if (possibility == sudokuGrid[columnCell(column, i)] && cell != columnCell(column, i)) {
			return false;
		}
	}

	// ...row
	for (i=0;i<SUDOKU_ROWS;i++) {
		if (possibility == sudokuGrid[rowCell(row, i)] && cell != rowCell(row, i)) {
			return false;
		}
	}

	// ...box
	for (i=0;i<SUDOKU_BOX_CELLS;i++) {
		if (possibility == sudokuGrid[boxCell(box, i)] && cell != boxCell(box, i)) {
			return false;
		}
	}
	return true;
}

enum status puzzleStatus(int sudokuGrid[SUDOKU_CELLS]){
	// the state is set to SOLVED only once at the beginning. If any problems
	// are found, the state will be changed and will not return SOLVED.
	enum status state = SOLVED;
	int i, j;
	for (i=0; i<SUDOKU_CELLS; i++) {

		// If the cell is empty, then we know that the puzzle MAY be unsolvable
		// and thus in a failed state...
		if (!sudokuGrid[i]) {
			state = FAILED;

			// However if the cell has any legal possible value, the puzzle
			// may not be in a failed state and the state is set back to
			// INCOMPLETE.
			for (j=0;j<SUDOKU_BOX_CELLS; j++) {
				if (isLegal(i, j, sudokuGrid)) {
					state = INCOMPLETE;
					break;
				}
			}

			// If however, there are no legal possible values for the cell,
			// the state will have remained FAILED.
			if (state == FAILED) {
				return FAILED;
			}

		}
	}
	return state;
}

//returns the cells number of 'member' of 'box'
int boxCell(int box, int member) {
	return (27*(box/3)) + (3*(box%3)) + (member%3) + (9*(member/3));
}

 //returns the box number of 'cell'
int cellBox(int cell) {
	return (3*(cellRow(cell)/3)) + (cellColumn(cell)/3);
}

//returns the cell number of 'member' of 'row'
int rowCell(int row, int member) {
	return (9*row) + member;
}

//returns row number of 'cell'
int cellRow(int cell) {
	return cell / 9;
}

//returns the cell number of 'member' of 'column'
int columnCell(int column, int member) {
	return (9*member) + column;
}

//returns column number of cell
int cellColumn(int cell) {
	return cell % 9;
}