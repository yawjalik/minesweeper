# minesweeper

**Team 59**:
- Yaw Jalik (3035729435)
- Guillemot Raphaele Michelle (3033093337)

**Description:**
Minesweeper, the game we all love/hate, in text-based format. Mines are randomly generated across the board and the player has to uncover all the empty blocks to win the game.

**Requirements:**
- Generation of random game sets or events → Randomly positioned mines
- Data structures for storing game status → Array for storing (a copy of) the board and additional game elements (lives/timer). 
- Dynamic memory management → Difficulty (board size/mines) or custom board sizes
- File input/output → Saving/loading external save-files
- Program codes in multiple files → Header files, helper functions (optional)

**Rough Implementation:**
- Initialize empty map → `void initialize_map(char[][]);`
- General function to print map → `void print_map(char[][]);`
- Randomly generate a number of mines → `void generate_mines(char[][]);`
- Generate clues (numbers) → `void generate_clues(char[][]);`
- Flag a block by taking additional player input (-f) → `void flag(char[][]);`
- Game loop → gets valid coordinate input from the player and uncovers the block. Loses if a mine is touched, wins if all empty blocks are uncovered.
- Save/load → stores/loads game status in an external file

**Additional features:**
- Encrypt the bomb positions on save to prevent players from cheating, decrypt on load.
- Cheat mode and codes.
- Main menu, with new/load game option, difficulty selector, etc...
- 3 lives, timer.
- system(“clear”) for a cleaner look.
- Different board shapes.
- Potential Story: clear the mine before the game releases viruses to affect your computer.


