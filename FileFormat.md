#File format used for gnonogram puzzles

# Introduction #

Gnonogram puzzles are stored as simple text files with a '.gno' extension. There are up to seven sections each of which is headed by a key word in square brackets. Only the [Dimensions](Dimensions.md) section is absolutely necessary. In addition to this you must have _either_ row and column clue sections _or_ a solution grid section.

An annotated example of such a file is shown below:


# Example .gno file #

```
[Description]  //Optional section 
Wave           //Descriptive name to display on screen
jeremy         //The name of the designer
2011-11-24     //The date created, in YYYY-MM-DD format
4              //An indication of difficulty (calculated by the computer solver)
[License]      //Optional section
CC-BY-SA       //Indication of the applicable copyright license (if applicable). Up to 50 characters
[Dimensions]   //Mandatory section. The puzzle will not load without it.
25             //The number of rows (1 - 100)
25             //The number of columns (1 - 100)
[Row clues]    //Mandatory if no solution grid provided
11,10          //Row clue 1
7,7            //Row clue 2
5,5            //  ....
4,4
2,3
1,2
2
1
1
4,1
5,1
5,1,1
5,1,1
7,1
7,2
7,2
9
6
3
3
1,1,2
4,2,1
4,5,1,1
5,7,2,1
15,4,2         //Row clue 25. Number of row clues must match the row dimension.
[Column clues] //Mandatory if no solution grid provided
6,4            //Column clue 1            
5,5            //Column clue 2
4,4            // ......
4,4
3,2
2,1
2,1
1,2
1,3
1,4
1,5
3
3
2
1
1,6
1,8
1,8,1
2,8,2
2,9,3
3,5,1
4,7
5,4
7,7,1
25          //Column clue 25.  Number of row clues must match the column dimension.
[Solution]  //Mandatory only if row and column clues are absent
2 2 2 2 2 2 2 2 2 2 2 1 1 1 1 2 2 2 2 2 2 2 2 2 2 //single digits separated by spaces
2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 //1=empty cell, 2= filled cell. 
2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 //number of lines = row dimension
2 2 2 2 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 //number of digits in line = column dimension 
2 2 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 
2 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 1 1 1 1 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 1 1 1 1 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 1 2 1 1 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 1 2 1 1 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 1 1 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 1 2 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 1 2 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 
1 2 1 1 1 1 1 1 1 1 2 1 1 1 1 1 1 1 1 1 1 1 1 2 2 
2 2 2 2 1 1 1 1 1 2 2 1 1 1 1 1 1 1 1 1 1 1 1 1 2 
2 2 2 2 1 1 1 1 2 2 2 2 2 1 1 1 1 1 1 2 1 1 1 1 2 
2 2 2 2 2 1 1 2 2 2 2 2 2 2 1 1 1 1 2 2 1 1 1 1 2 
2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 1 1 2 2 2 2 1 1 2 2 
[Working grid] // Generated if the puzzle is saved in the middle of solving it. 
2 2 2 2 2 2 2 2 2 2 2 1 1 1 1 2 2 2 2 2 2 2 2 2 2 //Format as for solution grid
2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 
2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 
2 2 2 2 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 
2 2 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 
2 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 1 1 1 1 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 1 1 1 1 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 1 2 1 1 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 1 2 1 1 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 1 1 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 1 2 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 1 2 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 
1 2 1 1 1 1 1 1 1 1 2 1 1 1 1 1 1 1 1 1 1 1 1 2 2 
2 2 2 2 1 1 1 1 1 2 2 1 1 1 1 1 1 1 1 1 1 1 1 1 2 
2 2 2 2 1 1 1 1 2 2 2 2 2 1 1 1 1 1 1 2 1 1 1 1 2 
2 2 2 2 2 1 1 2 2 2 2 2 2 2 1 1 1 1 2 2 1 1 1 1 2 
2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 1 1 2 2 2 2 1 1 2 2 
[State] //Generated when puzzle is saved by gnonograms program, records state of program, which is re-established when the puzzle is reloaded.
GAME_STATE_SETTING  // alternatively GAME_STATE_SOLVING
```