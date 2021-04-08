#include <iostream>
#include <string> // string inputs
#include <cctype>
#include <limits> //
#include <chrono> // time function in end summary
#include <cmath>  // floor division in end summary
#include "functions.h"
#include "prints.h"
using namespace std;

// ASCII text generated by https://fsymbols.com/text-art/

int main()
{
    // Main Menu
    string command;
    bool menu_started = false; // for the cin cout problem
    while (true)
    {
        // Print main menu and get input:
        cout << "\033[H\033[J";
        cout << "█▀▄▀█  ▀  █▀▀▄ █▀▀ █▀▀ █   █ █▀▀ █▀▀ █▀▀█ █▀▀ █▀▀█" << endl;
        cout << "█ ▀ █ ▀█▀ █  █ █▀▀ ▀▀█ █▄█▄█ █▀▀ █▀▀ █  █ █▀▀ █▄▄▀" << endl;
        cout << "▀   ▀ ▀▀▀ ▀  ▀ ▀▀▀ ▀▀▀  ▀ ▀  ▀▀▀ ▀▀▀ █▀▀▀ ▀▀▀ ▀ ▀▀" << endl;
        cout << "\n0. Instructions   1. New Game   2. Load Game   3. Quit" << endl;
        cout << ">> ";
        if (menu_started)
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, command);
        menu_started = true;

        if (command == "0")
        {
            cout << "\033[H\033[J";
            print_instructions();
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
            bool game_started = false; // also for cin cout problem

            // SELECT DIFFICULTY
            cout << "\nSELECT DIFFICULTY" << endl;
            cout << "1. Easy   2. Medium   3. Hard   4. Holy Shit\n";
            while (69 < 420) // lmao nice
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

            // Start clock
            auto begin = chrono::high_resolution_clock::now();

            // Game Loop
            while (true)
            {
                bool flag = false;
                cout << "\033[H\033[J";
                print_board(coords_uncovered, ROWS, COLS);
                // print_board(board, ROWS, COLS);
                cout << ">> ";
                if (!game_started)
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, input); // a0, b1, etc.
                game_started = true;

                // Exit and save commands
                if (input == "quit" || input == "exit")
                {
                    delete_board(board, ROWS);
                    delete_board(coords_uncovered, ROWS);
                    menu_started = false;
                    break;
                }
                else if (input == "save")
                {
                    if (!save_board(board, coords_uncovered, ROWS, COLS, uncovered, total_mines))
                        cout << "Save failed :(" << endl;
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
                // if flag function
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
                    // Logistics- Time
                    auto end = chrono::high_resolution_clock::now();
                    auto elapsed = chrono::duration_cast<chrono::seconds>(end - begin);

                    // Logistics- flags
                    int flaggedBombs = 0;
                    for (int i = 0; i < ROWS; i++)
                    {
                        for (int j = 0; j < COLS; j++)
                        {
                            if (board[i][j] == 'X' && coords_uncovered[i][j] == '?')
                                flaggedBombs++;
                        }
                    }

                    cout << "\033[H\033[J";

                    cout << "█▀▀ ▄▀█ █▀▄▀█ █▀▀   █▀█ █ █ █▀▀ █▀█" << endl;
                    cout << "█▄█ █▀█ █ ▀ █ ██▄   █▄█ ▀▄▀ ██▄ █▀▄\n"
                         << endl;

                    print_board(board, ROWS, COLS);
                    cout << endl;

                    cout << "Mode: ";
                    if (difficulty == "1")
                        cout << "Easy" << endl;
                    else if (difficulty == "2")
                        cout << "Medium" << endl;
                    else if (difficulty == "3")
                        cout << "Hard" << endl;
                    else if (difficulty == "4")
                        cout << "Holy Shit" << endl;
                    cout << "Time: ";
                    if ((elapsed.count() / 60) > 1)
                        cout << floor(elapsed.count() / 60) << " minutes and " << (elapsed.count() % 60) << " seconds" << endl;
                    else if ((elapsed.count() / 60) >= 1)
                        cout << floor(elapsed.count() / 60) << " minute and " << (elapsed.count() % 60) << " seconds" << endl;
                    else
                        cout << elapsed.count() << " seconds" << endl;
                    cout << "Mines travelled: " << uncovered << endl;
                    cout << "Bombs flagged: " << flaggedBombs << "/" << total_mines << endl;

                    cout << "\nEnter any value to return to menu" << endl;
                    cout << ">> ";
                    delete_board(board, ROWS);
                    delete_board(coords_uncovered, ROWS);
                    cin >> input;
                    menu_started = false;
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
                    // Logistics- Time
                    auto end = chrono::high_resolution_clock::now();
                    auto elapsed = chrono::duration_cast<chrono::seconds>(end - begin);

                    // Logistics- flags
                    int flaggedBombs = 0;
                    for (int i = 0; i < ROWS; i++)
                    {
                        for (int j = 0; j < COLS; j++)
                        {
                            if (board[i][j] == 'X' && coords_uncovered[i][j] == '?')
                                flaggedBombs++;
                        }
                    }

                    cout << "\033[H\033[J";

                    cout << "█▀▀ █▀█ █▄ █ █▀▀ █▀█ ▄▀█ ▀█▀ █ █ █   ▄▀█ ▀█▀ █ █▀█ █▄ █ █▀" << endl;
                    cout << "█▄▄ █▄█ █ ▀█ █▄█ █▀▄ █▀█  █  █▄█ █▄▄ █▀█  █  █ █▄█ █ ▀█ ▄█\n"
                         << endl;

                    print_board(board, ROWS, COLS);
                    cout << endl;

                    cout << "Mode: ";
                    if (difficulty == "1")
                        cout << "Easy" << endl;
                    else if (difficulty == "2")
                        cout << "Medium" << endl;
                    else if (difficulty == "3")
                        cout << "Hard" << endl;
                    else if (difficulty == "4")
                        cout << "Holy Shit" << endl;
                    cout << "Time: ";
                    if ((elapsed.count() / 60) > 1)
                        cout << floor(elapsed.count() / 60) << " minutes and " << (elapsed.count() % 60) << " seconds" << endl;
                    else if ((elapsed.count() / 60) >= 1)
                        cout << floor(elapsed.count() / 60) << " minute and " << (elapsed.count() % 60) << " seconds" << endl;
                    else
                        cout << elapsed.count() << " seconds" << endl;
                    cout << "Mines travelled: " << uncovered << endl;
                    cout << "Bombs flagged: " << flaggedBombs << "/" << total_mines << endl;

                    cout << "\nEnter any value to return to menu" << endl;
                    cout << ">> ";
                    delete_board(board, ROWS);
                    delete_board(coords_uncovered, ROWS);
                    cin >> input;
                    menu_started = false;
                    break;
                }
            }
        }
        else if (command == "2")
        {
            int ROWS, COLS, uncovered, total_mines;
            string input, difficulty;
            char **board = NULL;
            char **coords_uncovered = NULL;
            if (!load_board(board, coords_uncovered, ROWS, COLS, uncovered, total_mines))
            {
                cout << "No save file detected\nEnter any value to return to menu" << endl;
                cin >> input;
                continue;
            }

            if (ROWS == 6 && COLS == 8)
            {
                difficulty == "1";
            }
            else if (ROWS == 8 && COLS == 10)
            {
                difficulty == "2";
            }
            else if (ROWS == 10 && COLS == 12)
            {
                difficulty == "3";
            }
            else if (ROWS == 18 && COLS == 20)
            {
                difficulty == "4";
            }


            // Declaring variables
            int row, col;              // user row col input
            bool game_started = false; // also for cin cout problem

            // Start clock
            auto begin = chrono::high_resolution_clock::now();

            // Game Loop
            while (true)
            {
                bool flag = false;
                cout << "\033[H\033[J";
                print_board(coords_uncovered, ROWS, COLS);
                // print_board(board, ROWS, COLS);
                cout << ">> ";
                // if (game_started)
                //     cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, input); // a0, b1, etc.
                // game_started = true; no cin cout issue i think

                // Exit and save commands
                if (input == "quit" || input == "exit")
                {
                    delete_board(board, ROWS);
                    delete_board(coords_uncovered, ROWS);
                    menu_started = false;
                    break;
                }
                else if (input == "save")
                {
                    if (!save_board(board, coords_uncovered, ROWS, COLS, uncovered, total_mines))
                        cout << "Save failed :(" << endl;
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
                // if flag function
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
                    // Logistics- Time
                    auto end = chrono::high_resolution_clock::now();
                    auto elapsed = chrono::duration_cast<chrono::seconds>(end - begin);

                    // Logistics- flags
                    int flaggedBombs = 0;
                    for (int i = 0; i < ROWS; i++)
                    {
                        for (int j = 0; j < COLS; j++)
                        {
                            if (board[i][j] == 'X' && coords_uncovered[i][j] == '?')
                                flaggedBombs++;
                        }
                    }

                    cout << "\033[H\033[J";

                    cout << "█▀▀ ▄▀█ █▀▄▀█ █▀▀   █▀█ █ █ █▀▀ █▀█" << endl;
                    cout << "█▄█ █▀█ █ ▀ █ ██▄   █▄█ ▀▄▀ ██▄ █▀▄\n"
                         << endl;

                    print_board(board, ROWS, COLS);
                    cout << endl;

                    cout << "Mode: ";
                    if (difficulty == "1")
                        cout << "Easy" << endl;
                    else if (difficulty == "2")
                        cout << "Medium" << endl;
                    else if (difficulty == "3")
                        cout << "Hard" << endl;
                    else if (difficulty == "4")
                        cout << "Holy Shit" << endl;
                    cout << "Time: ";
                    if ((elapsed.count() / 60) > 1)
                        cout << floor(elapsed.count() / 60) << " minutes and " << (elapsed.count() % 60) << " seconds" << endl;
                    else if ((elapsed.count() / 60) >= 1)
                        cout << floor(elapsed.count() / 60) << " minute and " << (elapsed.count() % 60) << " seconds" << endl;
                    else
                        cout << elapsed.count() << " seconds" << endl;
                    cout << "Mines travelled: " << uncovered << endl;
                    cout << "Bombs flagged: " << flaggedBombs << "/" << total_mines << endl;

                    cout << "\nEnter any value to return to menu" << endl;
                    cout << ">> ";
                    delete_board(board, ROWS);
                    delete_board(coords_uncovered, ROWS);
                    cin >> input;
                    menu_started = false;
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
                    // Logistics- Time
                    auto end = chrono::high_resolution_clock::now();
                    auto elapsed = chrono::duration_cast<chrono::seconds>(end - begin);

                    // Logistics- flags
                    int flaggedBombs = 0;
                    for (int i = 0; i < ROWS; i++)
                    {
                        for (int j = 0; j < COLS; j++)
                        {
                            if (board[i][j] == 'X' && coords_uncovered[i][j] == '?')
                                flaggedBombs++;
                        }
                    }

                    cout << "\033[H\033[J";

                    cout << "█▀▀ █▀█ █▄ █ █▀▀ █▀█ ▄▀█ ▀█▀ █ █ █   ▄▀█ ▀█▀ █ █▀█ █▄ █ █▀" << endl;
                    cout << "█▄▄ █▄█ █ ▀█ █▄█ █▀▄ █▀█  █  █▄█ █▄▄ █▀█  █  █ █▄█ █ ▀█ ▄█\n"
                         << endl;

                    print_board(board, ROWS, COLS);
                    cout << endl;

                    cout << "Mode: ";
                    if (difficulty == "1")
                        cout << "Easy" << endl;
                    else if (difficulty == "2")
                        cout << "Medium" << endl;
                    else if (difficulty == "3")
                        cout << "Hard" << endl;
                    else if (difficulty == "4")
                        cout << "Holy Shit" << endl;
                    cout << "Time: ";
                    if ((elapsed.count() / 60) > 1)
                        cout << floor(elapsed.count() / 60) << " minutes and " << (elapsed.count() % 60) << " seconds" << endl;
                    else if ((elapsed.count() / 60) >= 1)
                        cout << floor(elapsed.count() / 60) << " minute and " << (elapsed.count() % 60) << " seconds" << endl;
                    else
                        cout << elapsed.count() << " seconds" << endl;
                    cout << "Mines travelled: " << uncovered << endl;
                    cout << "Bombs flagged: " << flaggedBombs << "/" << total_mines << endl;

                    cout << "\nEnter any value to return to menu" << endl;
                    cout << ">> ";
                    delete_board(board, ROWS);
                    delete_board(coords_uncovered, ROWS);
                    cin >> input;
                    menu_started = false;
                    break;
                }
            }
        }
        else if (command == "3")
        {
            cout << "\033[H\033[J";
            cout << "█▀▀ █▀█ █▀█ █▀▄ █▄▄ █▄█ █▀▀ █" << endl;
            cout << "█▄█ █▄█ █▄█ █▄▀ █▄█  █  ██▄ ▄" << endl;
            break;
        }
        else
        {
            menu_started = false;
        }
    }

    return 0;
}
