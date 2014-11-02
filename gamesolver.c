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
                  |to the pencilIn() function|    +-----------+-----------+    
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
| |Return the|  no |Does the first cell that |    |possible value inserted.|  |
| |failed    <-----+you try have at least one+---->This is then sent to    |  |
| |puzzle.   |     |possible value?          |    |solveSudoku().          |  |
| +----------+     +-------------------------+    +------------------------+  |
|                                                                             |
|                                                                             |
+-----------------------------------------------------------------------------+

*/



// The main function, this accepts puzzles and uses other functions to solve 
// them
solveSudoku(int sudokuGrid[SUDOKU_CELLS]) {
								  //returns 1 if solved, -1 if failed.
	int i, j, result;
	while (pencilIn(sudokuGrid) || crossHatching(sudokuGrid)) {
		;
	}
	switch(isSolved(sudokuGrid)) {
		case 1:
			return 1;
		case 0:
			return constraintSearch(sudokuGrid); //constraint search should always solve the problem in theory.
		case -1:
			return -1;
	}
}

constraintSearch(int sudokuGrid[SUDOKU_CELLS]) { //
	int theocell;
	int theogrid[SUDOKU_CELLS];
	int i;

	// Find the first empty cell in the sudoku puzzle
	for (i=0;i<SUDOKU_CELLS;i++) {
		if (!sudokuGrid[i]) {
			theocell = i;
			break;
		}
	}

	// Find the first possible number that could go into that cell and try to
	// solve the puzzle with that. The guess will be wrong if the puzzle comes back failed and so a new guess will be tried in the same cell. This conitinues until the puzzle comes back solved or 
	for (i=1;i<=SUDOKU_BOX_CELLS;i++) {
		setGrid(sudokuGrid, theogrid);
		if (isLegal(theocell, i, sudokuGrid)) { //find a possibility in that cell
			theogrid[theocell] = i; //set that possibility to the empty cell
			switch (solveSudoku(theogrid)) { //attempt to solve
				case -1: //if it fails
					continue;
				case 1:
					setGrid(theogrid, sudokuGrid);
					return 1;
			}
		}
	}
	return -1;
}

pencilIn(int sudokuGrid[SUDOKU_CELLS]) { //sets cells which have only one possibility. returns 1 if solved a cell, else 0
	int cell, i , j;
	int result = 0;
	for (cell=0;cell<SUDOKU_CELLS;cell++) { //for each cell in the sudoku puzzle
		if (sudokuGrid[cell]) { //skip if cell is not empty
			continue;
		}
		for (i=1;i<SUDOKU_BOX_CELLS;i++) { //for each possibility for each cell
			if (isLegal(cell, i, sudokuGrid)) {
				if (sudokuGrid[cell]) { //if a second possibility is found, set cell to zero and try next cell
					sudokuGrid[cell] = 0;
					break;
				}
				else {
					sudokuGrid[cell] = i;
				}
			}
		}
		if (sudokuGrid[cell]) {
			result = 1;
		}
	}
	return result;
}

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

setGrid(int from[SUDOKU_CELLS], int to[SUDOKU_CELLS]) { //turns 'to' into an identical copy of 'from'
	int i;
	for (i=0;i<SUDOKU_CELLS;i++) {
		to[i] = from[i];
	}
	return 0;
}

int isLegal(int cell, int possibility, int sudokuGrid[SUDOKU_CELLS]) { //is 'possibility' legal in 'cell' of the 'sudokuGrid'
	int i;
	int column = cellColumn(cell);
	int row = cellRow(cell);
	int box = cellBox(cell);

	for (i=0;i<SUDOKU_COLUMNS;i++) {
		if (possibility == sudokuGrid[columnCell(column, i)] && cell != columnCell(column, i)) {
			return 0;
		}
	}
	for (i=0;i<SUDOKU_ROWS;i++) {
		if (possibility == sudokuGrid[rowCell(row, i)] && cell != rowCell(row, i)) {
			return 0;
		}
	}	
	for (i=0;i<SUDOKU_BOX_CELLS;i++) {
		if (possibility == sudokuGrid[boxCell(box, i)] && cell != boxCell(box, i)) {
			return 0;
		}
	}
	return 1;
}

int isSolved(int sudokuGrid[SUDOKU_CELLS]){ // -1 Failed | 0 Unsolved | 1 Solved
	int cell, legalsfound, i;
	int status = 0;
	for (cell=0;cell<SUDOKU_CELLS;cell++) {
		if (!sudokuGrid[cell]) { //if an empty cell is found
			legalsfound = 0;
			for (i=1;i<=SUDOKU_BOX_CELLS;i++) {
				if (isLegal(cell, i, sudokuGrid)) {
					legalsfound++;
				}
			}
			if (legalsfound) {
				status = 2;
			}
			else {
				return -1;
			}
		}
		else { //if non empty
			if (!isLegal(cell, sudokuGrid[cell], sudokuGrid)) {
				return -1;
			}
			if (status < 2) {
				status = 1;
			}
		}
	}
	switch (status) {
		case 1:
			return 1;
		case 2:
			return 0;
	}
}

int boxCell(int box, int member) { //returns the cells number of 'member' of 'box'
	return (27*(box/3)) + (3*(box%3)) + (member%3) + (9*(member/3));
}

int cellBox(int cell) { //returns the box number of 'cell'
	return (3*(cellRow(cell)/3)) + (cellColumn(cell)/3);
}

int rowCell(int row, int member) { //returns the cell number of 'member' of 'row'
	return (9*row) + member;
}

int cellRow(int cell) { //returns row number of 'cell'
	return cell / 9;
}

int columnCell(int column, int member) { //returns the cell number of 'member' of 'column'
	return (9*member) + column;
}

int cellColumn(int cell) { //returns column number of cell
	return cell % 9;
}