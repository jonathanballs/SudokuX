#SudokuX

##Files included

###sudokux.c
This is the source file that contains the main function. This part of the program doesn't actually reads the problems from the command line or an input file. After being solved, it displays them in a terminal UI with ncurses.

###gamesolver.c
This is the part which actually solves each sudoku. I have commented how it works so go give it a read!

###examplefiles/
I have included two files in this directory which contain a number of sudoku problems to test the file with.

##HOWTO compile
$ make
There are some dependencies needed to make this work but make shall tell you.

##HOWTO run
$ ./sudokux exampleproblems/small


##Examplel output

                                     small


             + - - - + - - - + - - - +    + - - - + - - - + - - - +
             | . 6 . | 3 . . | 8 . 4 |    | 2 6 1 | 3 7 5 | 8 9 4 |
             | 5 3 7 | . 9 . | . . . |    | 5 3 7 | 8 9 4 | 1 6 2 |
             | . 4 . | . . 6 | 3 . 7 |    | 9 4 8 | 2 1 6 | 3 5 7 |
             + - - - + - - - + - - - +    + - - - + - - - + - - - +
             | . 9 . | . 5 1 | 2 3 8 |    | 6 9 4 | 7 5 1 | 2 3 8 |
             | . . . | . . . | . . . |    | 8 2 5 | 9 4 3 | 6 7 1 |
             | 7 1 3 | 6 2 . | . 4 . |    | 7 1 3 | 6 2 8 | 9 4 5 |
             + - - - + - - - + - - - +    + - - - + - - - + - - - +
             | 3 . 6 | 4 . . | . 1 . |    | 3 5 6 | 4 8 2 | 7 1 9 |
             | . . . | . 6 . | 5 2 3 |    | 4 8 9 | 1 6 7 | 5 2 3 |
             | 1 . 2 | . . 9 | . 8 . |    | 1 7 2 | 5 3 9 | 4 8 6 |
             + - - - + - - - + - - - +    + - - - + - - - + - - - +

                        Sudoku Number:    1
                               Solved:    1
                               Failed:    0
                             Unsolved:    0
                            Remaining:    1012