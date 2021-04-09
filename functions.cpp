#include <iostream>
#include <string>  // string inputs
#include <cstdlib> // rand
#include <ctime>
#include <fstream>
#include "functions.h"
#include "prints.h"
using namespace std;

void initialize_board(char **board, int ROWS, int COLS, char letter)
{
    for (int i = 0; i < ROWS; i++)
    {
        board[i] = new char[COLS];
        for (int j = 0; j < COLS; j++)
        {
            board[i][j] = letter;
        }
    }
}

bool load_board(char **&board, char **&coords_uncovered, int &ROWS, int &COLS, int &uncovered, int &total_mines)
{
    ifstream fin("savefile.txt");
    if (fin.fail())
        return false;

    fin >> ROWS >> COLS >> uncovered >> total_mines;

    board = new char *[ROWS];
    for (int i = 0; i < ROWS; i++)
    {
        board[i] = new char[COLS];
        for (int j = 0; j < COLS; j++)
        {
            fin >> board[i][j];
        }
    }

    coords_uncovered = new char *[ROWS];
    for (int i = 0; i < ROWS; i++)
    {
        coords_uncovered[i] = new char[COLS];
        for (int j = 0; j < COLS; j++)
        {
            fin >> coords_uncovered[i][j];
        }
    }
    fin.close();
    return true;
}

int generate_mines(char **board, int ROWS, int COLS)
{
    srand(time(NULL));
    int count = 0;
    int total_mines = (ROWS * COLS * 0.125);
    // cout << "Total number of mines: " << total_mines << endl;
    while (count < total_mines)
    {
        int row = rand() % ROWS;
        int col = rand() % COLS;
        if (board[row][col] != 'X')
        {
            board[row][col] = 'X';
            count++;
        }
    }
    return total_mines;
}

void generate_clues(char **board, int ROWS, int COLS)
{
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            if (board[row][col] == 'X')
            {
                // check if it doesn't touch the borders or isn't a mine, then add 1 on the tiles
                if (col > 0 && board[row][col - 1] != 'X') // check left/right
                    board[row][col - 1] += 1;

                if (col < COLS && board[row][col + 1] != 'X')
                    board[row][col + 1] += 1;

                // check top row
                if (row > 0)
                {
                    if (board[row - 1][col] != 'X') // if not X
                        board[row - 1][col] += 1;
                    if (col > 0 && board[row - 1][col - 1] != 'X') // and if left/right are fine too
                        board[row - 1][col - 1] += 1;
                    if (col < COLS && board[row - 1][col + 1] != 'X')
                        board[row - 1][col + 1] += 1;
                }

                // check bottom row
                if (row < ROWS - 1)
                {
                    if (board[row + 1][col] != 'X') // if not X
                        board[row + 1][col] += 1;
                    if (col > 0 && board[row + 1][col - 1] != 'X') // and if left/right are fine too
                        board[row + 1][col - 1] += 1;
                    if (col < COLS && board[row + 1][col + 1] != 'X')
                        board[row + 1][col + 1] += 1;
                }
            }
        }
    }
}

void delete_board(char **board, int ROWS)
{
    for (int i = 0; i < ROWS; i++)
    {
        delete[] board[i];
    }
    delete[] board;
}

bool save_board(char **board, char **coords_uncovered, int ROWS, int COLS, int uncovered, int total_mines)
{
    // Override warning
    string input;
    ifstream fin("savefile.txt");
    if (!fin.fail())
    {
        cout << "Existing save file detected. Override it? y/n" << endl;
        while (true)
        {
            cout << ">> ";
            cin >> input;
            if (input == "y")
                break;
            else if (input == "n")
            {
                fin.close();
                return false;
            }
        }
    }
    fin.close();

    ofstream fout("savefile.txt");
    if (fout.fail())
    {
        delete_board(board, ROWS);
        return false;
    }

    // Save ROWS, COLS, uncovered, total_mines into the first line
    fout << ROWS << ' ' << COLS << ' ' << uncovered << ' ' << total_mines << '\n';

    // Save the board
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            fout << board[i][j] << ' ';
        }
        fout << '\n';
    }

    // Save the other board
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            fout << coords_uncovered[i][j] << ' ';
        }
        fout << '\n';
    }

    fout.close();
    cout << "Saved Successfully\nEnter any value to return" << endl;
    cin >> input;
    return true;
}

void flood_fill(char **board, char **coords_uncovered, int ROWS, int COLS, int row, int col, int &uncovered)
{
    // If already uncovered
    if (coords_uncovered[row][col] != '*')
        return;

    // If not a zero
    if (board[row][col] != '0')
    {
        coords_uncovered[row][col] = board[row][col];
        uncovered++;
        return;
    }

    coords_uncovered[row][col] = '0';
    uncovered++;

    // Left Right Up Down
    if (row < ROWS - 1)
        flood_fill(board, coords_uncovered, ROWS, COLS, row + 1, col, uncovered);
    if (row > 0)
        flood_fill(board, coords_uncovered, ROWS, COLS, row - 1, col, uncovered);
    if (col > 0)
        flood_fill(board, coords_uncovered, ROWS, COLS, row, col - 1, uncovered);
    if (col < COLS - 1)
        flood_fill(board, coords_uncovered, ROWS, COLS, row, col + 1, uncovered);

    // Four corners
    if (row > 0 && col < COLS - 1)
        flood_fill(board, coords_uncovered, ROWS, COLS, row - 1, col + 1, uncovered);
    if (row < ROWS - 1 && col > 0)
        flood_fill(board, coords_uncovered, ROWS, COLS, row + 1, col - 1, uncovered);
    if (row > 0 && col > 0)
        flood_fill(board, coords_uncovered, ROWS, COLS, row - 1, col - 1, uncovered);
    if (row < ROWS - 1 && col < COLS - 1)
        flood_fill(board, coords_uncovered, ROWS, COLS, row + 1, col + 1, uncovered);
}

void game_loop(char **board, char **coords_uncovered, int ROWS, int COLS, int uncovered, int total_mines, bool &game_started, bool &menu_started, char difficulty)
{
    // Variables
    string input;
    int row, col; // user row col input

    // Start clock
    auto begin = chrono::high_resolution_clock::now();

    while (true)
    {
        bool flag = false;
        //cout << "\033[H\033[J";
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
        else if (input.length() == 2 && islower(input[0]) && isdigit(input[1]))
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

        // Flood fill
        if (board[row][col] == '0' && !flag && coords_uncovered[row][col] != '?')
        {
            flood_fill(board, coords_uncovered, ROWS, COLS, row, col, uncovered);
        }

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
            print_summary(difficulty, elapsed.count(), uncovered, flaggedBombs, total_mines);

            delete_board(board, ROWS);
            delete_board(coords_uncovered, ROWS);
            cin >> input;
            menu_started = false;
            break;
        }
        cout << row << col << coords_uncovered[row][col] << endl;
        // Toggle flagging
        if (flag && coords_uncovered[row][col] == '?')
            coords_uncovered[row][col] = '*';
        else if (flag && coords_uncovered[row][col] == '*')
            coords_uncovered[row][col] = '?';
        // Uncovering square
        else if (coords_uncovered[row][col] == '*')
        {
            cout << "HI" << endl;
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
            print_summary(difficulty, elapsed.count(), uncovered, flaggedBombs, total_mines);

            delete_board(board, ROWS);
            delete_board(coords_uncovered, ROWS);
            cin >> input;
            menu_started = false;
            break;
        }
    }
}
