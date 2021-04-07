#include <iostream>
#include <string>
#include <cctype>
#include "functions.h"
using namespace std;

// ASCII text generated by https://fsymbols.com/text-art/

int main()
{
    // Main Menu
    string command;
    while (true)
    {
        // Print main menu and get input:
        cout << "\033[H\033[J";
        cout << "█▀▄▀█ █ █▄░█ █▀▀ █▀ █░█░█ █▀▀ █▀▀ █▀█ █▀▀ █▀█" << endl;
        cout << "█░▀░█ █ █░▀█ ██▄ ▄█ ▀▄▀▄▀ ██▄ ██▄ █▀▀ ██▄ █▀▄\n"
             << endl;
        cout << "0. Instructions   1. New Game   2. Load Game   3. Quit" << endl;
        cout << ">> ";
        getline(cin, command);

        if (command == "0")
        {
            cout << "\033[H\033[J";
            cout << "█▀▄▀█ █ █▄░█ █▀▀ █▀ █░█░█ █▀▀ █▀▀ █▀█ █▀▀ █▀█" << endl;
            cout << "█░▀░█ █ █░▀█ ██▄ ▄█ ▀▄▀▄▀ ██▄ ██▄ █▀▀ ██▄ █▀▄\n"
                 << endl;
            string input;
            cout << "WIN by uncovering all the unarmed mines \nLOSE by stepping on an armed mine \n \n";

            cout << "each mine will have a number indicating how many BOMBS are around it \n e.g. a mine with the number 2 indicates that there are 2 bombs next to it \n \n";

            cout << "UNCOVER by typing in the coordinates of the mine \n e.g. >> a0 \n \n";

            cout << "add and remove FLAGS with ? to note down possible armed locations and prevent tripping them \n e.g. >> ?a0 \n \n";

            cout << "Enter any value to return to menu" << endl;

            cout << ">> ";
            cin >> input;
            continue;
        }

        else if (command == "1")
        {
            // Declaring variables
            string input;
            int ROWS, COLS; // Max board size
            int row, col;   // user row col input
            int total_mines, uncovered = 0;
            string difficulty;

            // SELECT DIFFICULTY
            cout << "\nSELECT DIFFICULTY" << endl;
            cout << "1. Easy   2. Medium   3. Hard   4. Holy Shit\n";
            while (true)
            {
                cout << ">> ";
                cin >> difficulty;
                if (difficulty == "1")
                {
                    ROWS = 6;
                    COLS = 8;
                    break;
                }
                else if (difficulty == "2")
                {
                    ROWS = 8;
                    COLS = 10;
                    break;
                }
                else if (difficulty == "3")
                {
                    ROWS = 10;
                    COLS = 12;
                    break;
                }
                else if (difficulty == "4")
                {
                    ROWS = 18;
                    COLS = 20;
                    break;
                }
            }

            // Initializing
            char **board = new char *[ROWS];
            initialize_board(board, ROWS, COLS, '0');
            char **coords_uncovered = new char *[ROWS];
            initialize_board(coords_uncovered, ROWS, COLS, '*');

            total_mines = generate_mines(board, ROWS, COLS);
            generate_clues(board, ROWS, COLS);

            // Game Loop
            while (true)
            {
                bool flag = false;
                cout << "\033[H\033[J";
                print_board(coords_uncovered, ROWS, COLS);
                cout << ">> ";
                getline(cin, input); // something like a0, b1, etc.

                // Temporary exit command
                if (input == "quit" || input == "exit")
                {
                    delete_board(board, ROWS);
                    delete_board(coords_uncovered, ROWS);
                    break;
                }

                // Check invalid input, set row col, check valid row col and no repeats
                if (input.length() == 3 && islower(input[0]) && isdigit(input[1]) && isdigit(input[2]))
                {
                    row = input[0] - 'a';
                    col = input[2] - '0' + 10;
                    // Check for limit and repeated row/col
                    if (row >= ROWS || col >= COLS || board[row][col] < '0')
                        continue;
                }
                if (input.length() == 2 && islower(input[0]) && isdigit(input[1]))
                {
                    row = input[0] - 'a';
                    col = input[1] - '0';
                    // Check for limit and repeated row/col
                    if (row >= ROWS || col >= COLS || board[row][col] < '0')
                        continue;
                }
                // if flag fuction
                else if (input.length() == 4 && input[0] == '?' && islower(input[1]) && isdigit(input[2]) && isdigit(input[3]))
                {
                    flag = true;
                    row = input[1] - 'a';
                    col = input[3] - '0' + 10;
                    if (row >= ROWS || col >= COLS || board[row][col] < '0')
                        continue;
                }
                else if (input.length() == 3 && input[0] == '?' && islower(input[1]) && isdigit(input[2]))
                {
                    flag = true;
                    row = input[1] - 'a';
                    col = input[2] - '0';
                    if (row >= ROWS || col >= COLS || board[row][col] < '0')
                        continue;
                }
                else
                    continue;

                // Losing condition
                if (board[row][col] == 'X' && !flag && coords_uncovered[row][col] != '?')
                {
                    //cout << "\033[H\033[J";
                    print_board(board, ROWS, COLS);
                    cout << "Game Over!\nEnter any value to return to menu" << endl;
                    delete_board(board, ROWS);
                    delete_board(coords_uncovered, ROWS);
                    cin >> input;
                    break;
                }

                // Toggle flagging
                if (flag && coords_uncovered[row][col] == '?')
                    coords_uncovered[row][col] = '*';
                else if (flag && coords_uncovered[row][col] == '*')
                    coords_uncovered[row][col] = '?';

                // Uncovering square
                else if (coords_uncovered[row][col] == '*')
                {
                    coords_uncovered[row][col] = board[row][col];
                    uncovered++;
                    cout << uncovered << endl;
                }

                // Winning condition
                if (uncovered == (ROWS * COLS - total_mines))
                {
                    cout << "\033[H\033[J";
                    print_board(board, ROWS, COLS);
                    cout << "You Win!\nEnter any value to return to menu" << endl;
                    delete_board(board, ROWS);
                    delete_board(coords_uncovered, ROWS);
                    cin >> input;
                    break;
                }
            }
        }
        else if (command == "2")
        {
            int ROWS, COLS;
            string input;
            char **board = new char *[ROWS];
            if (!load_board(board, ROWS, COLS))
            {
                delete[] board;
                cout << "No save file detected\nEnter any value to return to menu" << endl;
                cin >> input;
                continue;
            }

            cout << "Loaded" << endl;
            // generate_mines(board, ROWS, COLS);
            delete[] board;
        }
        else if (command == "3")
        {
            cout << "\033[H\033[J";
            cout << "█▀▀ █▀█ █▀█ █▀▄ █▄▄ █▄█ █▀▀ █" << endl;
            cout << "█▄█ █▄█ █▄█ █▄▀ █▄█ ░█░ ██▄ ▄" << endl;
            break;
        }
    }

    return 0;
}
