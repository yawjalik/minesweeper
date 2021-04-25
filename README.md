<!-- @format -->

# Minesweeper

**Team 59:**
- YAW Jalik (3035729435)
- GUILLEMOT Raphaele Michelle (3033093337)
- **Project:** Minesweeper, the game we all love/hate, in text-based format. Mines are randomly generated across the board and the player has to uncover all the empty blocks to win the game. Players have the option to choose a new game or load game with a save-file.

---

## **Files List**

- `board.cpp` The struct Board and functions related to the board engine
- `board.h` board.cpp headers
- `functions.cpp` The helper functions for easy read and run logic flow
- `functions.h` functions.cpp headers
- `main.cpp` Dictates the flow of the game and compiles all the functions
- `Makefile` Makefile to build minesweeper
- `prints.cpp` The functions that only needs to print and convey information
- `prints.h` prints.cpp headers
- `README.md` This file

Program can be built using 'make main' on the terminal.

---

## **Design Decisions**

1. Generation of random game sets or events
- Randomly generated mines that are dependant on the first move
  (board.cpp, `Board::generate_mines()`)

2. Data structures for storing game status
- Board struct that stores information of the minesweeper board (board.cpp, `Board::Board()`)
- Other variables that kept track of the game are `string input`, `int row, col` (main.cpp, 47)
- `int previous_time` is a special variable that traverses through different save files to keep an accurate measurement of the gameplay time

3. Dynamic memory management
- Two dynamic 2D char arrays representing game boards that have sizes dependant on difficulty
  (board.cpp, `Board::initialize_board()`, `Board::select_difficulty()`)
- deletion of boards to free memory space (board.cpp, `Board::~Board()`)

4. File input/output
- Saving/loading external save-file in `savefile.txt`
  (board.cpp, `Board::load_board()`, `Board::save_board()`)

5. Program codes in multiple files (board.cpp, functions.cpp, main.cpp, prints.cpp)

6. Proper indentation and naming styles

7. In-code documentation in the beginning of every `.cpp` file and throughout

*** Program compiled and tested in both academy11 and academy21 servers
*** input and output files in sample_gameplay are only for reference, NOT suitable for automated testing as the game is random.

---

## **External libraries/sources used**
- No external libraries used
- ASCII text generated by https://fsymbols.com/text-art/
- Text symbols (in print_board) generated by https://www.madeintext.com/text-symbols/
- Flood fill idea https://stackoverflow.com/questions/19633718/minesweeper-board-opening-up
- Clearing screen https://stackoverflow.com/questions/5367068/clear-a-terminal-screen-for-real
