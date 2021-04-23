# minesweeper

**Team 59:**
- Yaw Jalik (3035729435)
- Guillemot Raphaele Michelle (3033093337)

**What is this?:**
Minesweeper, the game we all love/hate, in text-based format. Mines are randomly generated across the board and the player has to uncover all the empty blocks to win the game.

**Getting started:**
- Ensure all files are present and in the same directory.
- Compile using the command 'make main' and let the Makefile do its magic.
- Run the game by typing './main'.
- When in the main menu, enter "0" to get the gameplay instructions and available commands.

**Game Features:**
- The program is separated into four files:
  1. main.cpp for the main menu and overall game flow.
  2. board.cpp & board.h for the board engine (a struct Board).
  3. functions.cpp & functions.h for additional helper functions.
  4. prints.cpp & prints.h for extra printing functions.
- TODO...

**Previous Ideas:**
- Initialize empty map → `void initialize_map(char[][]);`
- General function to print map → `void print_map(char[][]);`
- Randomly generate a number of mines → `void generate_mines(char[][]);`
- Generate clues (numbers) → `void generate_clues(char[][]);`
- Flag a block by taking additional player input (-f) → `void flag(char[][]);`
- Game loop → gets valid coordinate input from the player and uncovers the block. Loses if a mine is touched, wins if all empty blocks are uncovered.
- Save/load → stores/loads game status in an external file
- Main menu, with new/load game option, difficulty selector,  timer
- system(“clear”) for a cleaner look.

**Requirements met:**
1. Generation of random game sets or events → Randomly generated mines
2. Data structures for storing game status → struct Board that stores a board's state
3. Dynamic memory management → Two dynamic arrays representing game boards that depend on difficulty
4. File input/output → Saving/loading external save-files in 'savefile.txt'
5. Program codes in multiple files → board, functions, prints, and main 
6. Proper indentation and naming styles → Probably fine
7. In-code documentation → Present
