1. How to compile and run your program?
    Compile all four files into a single executable file

2. What are the new functionalities that you implement?
    1. First sweep would never step onto a mine
    2. Winning condition changed to: when all non-MINE cells are swept, it is considered as Win
    3. The middle click function of the original game: when the number of marks surrounding it is same as the nearby mines count of that cell, middle clicking on that cell will sweep the surrounding non-marked and non-swept cells. In my implementation, this is integrated to op == 1, when you choose to sweep on a swept cell, it will perform this action if the condition is satisfied
    4. Custom mode support, the player can custom the game board

3. Give us a sample input and the corresponding output that your bonus program will produce.

    3. Middle click function (in this case, as cell(1,2) have 1 mine surrounding and have 1 marked cell surrounding, it satisfies the condition and hence cell(0,1) and cell(2,1) are swept by the function)
        ********** current state **********
        life = 3	marked = 1/10
              0   1   2   3   4   5   6   7   8
             --- --- --- --- --- --- --- --- ---
        0	| X | X | P | 1 |   | 1 | X | 1 |   |
             --- --- --- --- --- --- --- --- ---
        1	| X | 3 | 1 | 1 |   | 1 | X | 1 |   |
             --- --- --- --- --- --- --- --- ---
        2	| X | X | 1 |   |   | 1 | 1 | 1 |   |
             --- --- --- --- --- --- --- --- ---
        3	| X | X | 1 |   |   |   |   |   |   |
             --- --- --- --- --- --- --- --- ---
        4	| X | X | 2 | * |   |   |   | * |   |
             --- --- --- --- --- --- --- --- ---
        5	| X | X | X | 2 | 1 |   |   |   |   |
             --- --- --- --- --- --- --- --- ---
        6	| X | X | X | X | 2 |   |   |   |   |
             --- --- --- --- --- --- --- --- ---
        7	| X | X | X | X | 4 | 2 | 1 |   |   |
             --- --- --- --- --- --- --- --- ---
        8	| X | X | X | X | X | X | 1 |   |   |
             --- --- --- --- --- --- --- --- ---
             What operation you want to choose:
             op (0: sweep	1: marked as mine	2: unmark a cell): 0
             which cell in the map: row col?
             1 2

             ********** current state **********
             life = 3	marked = 1/10
              0   1   2   3   4   5   6   7   8
             --- --- --- --- --- --- --- --- ---
        0	| X | 3 | P | 1 |   | 1 | X | 1 |   |
             --- --- --- --- --- --- --- --- ---
        1	| X | 3 | 1 | 1 |   | 1 | X | 1 |   |
             --- --- --- --- --- --- --- --- ---
        2	| X | 2 | 1 |   |   | 1 | 1 | 1 |   |
             --- --- --- --- --- --- --- --- ---
        3	| X | X | 1 |   |   |   |   |   |   |
             --- --- --- --- --- --- --- --- ---
        4	| X | X | 2 | * |   |   |   | * |   |
             --- --- --- --- --- --- --- --- ---
        5	| X | X | X | 2 | 1 |   |   |   |   |
             --- --- --- --- --- --- --- --- ---
        6	| X | X | X | X | 2 |   |   |   |   |
             --- --- --- --- --- --- --- --- ---
        7	| X | X | X | X | 4 | 2 | 1 |   |   |
            --- --- --- --- --- --- --- --- ---
        8   | X | X | X | X | X | X | 1 |   |   |
             --- --- --- --- --- --- --- --- ---
             What operation you want to choose:
             op (0: sweep	1: marked as mine	2: unmark a cell):

    4. Custom mode sample IO
        -.-.-.- Mine Sweeper -.-.-.-

        * Choose a level to start:
         1. Beginner: 	9 * 9 board, 10 mines, 2 flowers
         2. Intermediate: 	16 * 16 board, 40 mines, 5 flowers
         3. Advanced: 	16 * 30 board, 99 mines, 10 flowers
         4. Custom
        Type 1 for Beginner, 2 for Intermediate, 3 for Advanced, 4 for Custom: 4

        * Choose mode:
        0. Play
        1. Debug
        Type 0 for Play mode, 1 for Debug mode: 0

        GAME START !!!  ATTENTION: Find flowers to have additional lives !!!
        input the height of the board (1 - 99): 2
        input the width of the board (1 - 99): 2
        input the number of mines (1 - 3): 3
        input the number of flowers (0 - 1): 1

        	 ********** current state **********
        	 life = 1	marked = 0/3
        	  0   1
        	 --- ---
        0	| X | X |
        	 --- ---
        1	| X | X |
        	 --- ---
        What operation you want to choose:
        op (0: sweep	1: marked as mine	2: unmark a cell):
