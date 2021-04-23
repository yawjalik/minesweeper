#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "functions.h"
#include "board.h"
using namespace std;

// Constructor
Board::Board()
{
    ROWS = 0;
    COLS = 0;
    total_mines = 0;
    uncovered = 0;
    raw_board = NULL;
    covered_board = NULL;
}

// Destructor
Board::~Board()
{
    delete_board(raw_board, ROWS);
    delete_board(covered_board, ROWS);
}

void Board::initialize_board()
{
    raw_board = new char*[ROWS];
    covered_board = new char*[ROWS];
    for (int i = 0; i < ROWS; i++)
    {
        raw_board[i] = new char[COLS];
        covered_board[i] = new char[COLS];
        for (int j = 0; j < COLS; j++)
        {
            raw_board[i][j] = '0';
            covered_board[i][j] = '*';
        }
    }
}

void Board::select_difficulty()
{
    // Select Difficulty
    string difficulty;
    cout << "\nSELECT DIFFICULTY" << endl;
    cout << "1. Easy   2. Medium   3. Hard   4. Holy Shit\n";
    while (true)
    {
        cout << ">> ";
        getline(cin, difficulty);
        if (difficulty == "1")
        {
            ROWS = 6;
            COLS = 8;
        }
        else if (difficulty == "2")
        {
            ROWS = 8;
            COLS = 10;
        }
        else if (difficulty == "3")
        {
            ROWS = 10;
            COLS = 12;
        }
        else if (difficulty == "4")
        {
            ROWS = 18;
            COLS = 20;
        }
        else
            continue;
        break;
    }
}

bool Board::load_board()
{
    ifstream fin("savefile.txt");
    if (fin.fail())
        return false;
    fin >> ROWS >> COLS >> total_mines >> uncovered;

    raw_board = new char*[ROWS];
    for (int i = 0; i < ROWS; i++)
    {
        raw_board[i] = new char[COLS];
        for (int j = 0; j < COLS; j++)
        {
            fin >> raw_board[i][j];
        }
    }

    covered_board = new char*[ROWS];
    for (int i = 0; i < ROWS; i++)
    {
        covered_board[i] = new char[COLS];
        for (int j = 0; j < COLS; j++)
        {
            fin >> covered_board[i][j];
        }
    }

    return true;
}

void Board::save_board()
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
            getline(cin, input);
            if (input == "y")
                break;
            else if (input == "n")
            {
                fin.close();
                return;
            }
        }
    }
    fin.close();

    ofstream fout("savefile.txt");
    if (fout.fail())
    {
        cout << "Save failed :(" << endl;
        return;
    }

    // Save ROWS, COLS, total_mines, uncovered into the first line
    fout << ROWS << ' ' << COLS << ' ' << total_mines << ' ' << uncovered << '\n';

    // Save the raw_board
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            fout << raw_board[i][j] << ' ';
        }
        fout << '\n';
    }

    // Save the covered_board
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            fout << covered_board[i][j] << ' ';
        }
        fout << '\n';
    }

    fout.close();
    cout << "Saved Successfully\nPress ENTER to continue" << endl;
    getline(cin, input);
}

// Prints either the raw or covered board, depending on argument
void Board::print_board(char **board)
{
    // Beginning space & column labels
    cout << "  ";
    for (int i = 0; i < COLS; i++)
    {
        if (i < 10)
            cout << "  " << i << " ";
        else
            cout << "  " << i;
    }
    cout << endl;

    // Separator
    cout << "  ┼";
    for (int i = 0; i < COLS; i++)
        cout << "–––┼";
    cout << endl;

    for (int i = 0; i < ROWS; i++)
    {
        // row labels + separator
        cout << char(i + 'a') << " │ ";

        // mine + border
        for (int j = 0; j < COLS; j++)
        {
            if (board[i][j] == '0')
                cout << ' ' << " │ ";
            else
                cout << board[i][j] << " │ ";
        }
        cout << endl;

        // border breathing space
        if (i != ROWS - 1)
            cout << "  ┼–";
        else
            cout << "  ╵ ";
        for (int j = 0; j < COLS; j++)
        {
            if (i == ROWS - 1 && j == COLS - 1)
                cout << "  ╵ ";
            else if (j == COLS - 1)
                cout << "––┼";
            else if (i != ROWS - 1)
                cout << "––┼–";
            else
                cout << "  ╵ ";
        }
        cout << endl;
    }
}

void Board::print_summary(int elapsed_time)
{
    int flaggedBombs = 0;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (raw_board[i][j] == 'X' && covered_board[i][j] == '?')
                flaggedBombs++;
        }
    }

    cout << "Mode: ";
    cout << get_difficulty() << endl;
    cout << "Time: ";
    if ((elapsed_time / 60) > 1)
        cout << elapsed_time / 60 << " minutes and " << (elapsed_time % 60) << " seconds" << endl;
    else if ((elapsed_time / 60) >= 1)
        cout << (elapsed_time / 60) << " minute and " << (elapsed_time % 60) << " seconds" << endl;
    else
        cout << elapsed_time << " seconds" << endl;
    cout << "Tiles uncovered: " << uncovered << '/' << ROWS * COLS - total_mines << endl;
    cout << "Bombs flagged: " << flaggedBombs << '/' << total_mines << endl;

    cout << "\nPress ENTER to return to menu ";
}

void Board::generate_mines(int row, int col)
{
    srand(time(NULL));
    int count = 0;
    total_mines = (ROWS * COLS * 0.125);
    while (count < total_mines)
    {
        int r = rand() % ROWS;
        int c = rand() % COLS;
        if (raw_board[r][c] != 'X' && (r != row) && (c != col) && (r != row + 1) && (c != col) + 1 && (r != row - 1) && (c != col - 1))
        {
            raw_board[r][c] = 'X';
            count++;
        }
    }
}

void Board::generate_clues()
{
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            if (raw_board[row][col] == 'X')
            {
                // check if it doesn't touch the borders or isn't a mine, then add 1 on the tiles
                if (col > 0)
                {
                    if (raw_board[row][col - 1] != 'X') // check left/right
                        raw_board[row][col - 1] += 1;
                }
                if (col < COLS)
                {
                    if (raw_board[row][col + 1] != 'X')
                        raw_board[row][col + 1] += 1;
                }
                // check top row
                if (row > 0)
                {
                    if (raw_board[row - 1][col] != 'X') // if not X
                        raw_board[row - 1][col] += 1;
                    if (col > 0)
                    {
                        if (raw_board[row - 1][col - 1] != 'X') // and if left/right are fine too
                            raw_board[row - 1][col - 1] += 1;
                    }
                    if (col < COLS)
                    {
                        if (raw_board[row - 1][col + 1] != 'X')
                            raw_board[row - 1][col + 1] += 1;
                    }
                }

                // check bottom row
                if (row < ROWS - 1)
                {
                    if (raw_board[row + 1][col] != 'X') // if not X
                        raw_board[row + 1][col] += 1;
                    if (col > 0)
                    {
                        if (raw_board[row + 1][col - 1] != 'X') // and if left/right are fine too
                            raw_board[row + 1][col - 1] += 1;
                    }
                    if (col < COLS)
                    {
                        if (raw_board[row + 1][col + 1] != 'X')
                            raw_board[row + 1][col + 1] += 1;
                    }
                }
            }
        }
    }
}

void Board::flood_fill(int row, int col)
{
    // If already uncovered
    if (covered_board[row][col] != '*')
        return;

    // If not a zero
    if (raw_board[row][col] != '0')
    {
        covered_board[row][col] = raw_board[row][col];
        uncovered++;
        return;
    }

    covered_board[row][col] = '0';
    uncovered++;

    // Left Right Up Down
    if (row < ROWS - 1)
        flood_fill(row + 1, col);
    if (row > 0)
        flood_fill(row - 1, col);
    if (col > 0)
        flood_fill(row, col - 1);
    if (col < COLS - 1)
        flood_fill(row, col + 1);

    // Four corners
    if (row > 0 && col < COLS - 1)
        flood_fill(row - 1, col + 1);
    if (row < ROWS - 1 && col > 0)
        flood_fill(row + 1, col - 1);
    if (row > 0 && col > 0)
        flood_fill(row - 1, col - 1);
    if (row < ROWS - 1 && col < COLS - 1)
        flood_fill(row + 1, col + 1);
}

string Board::get_difficulty()
{
    if (ROWS == 6 && COLS == 8)
    {
        return "Easy";
    }
    else if (ROWS == 8 && COLS == 10)
    {
        return "Medium";
    }
    else if (ROWS == 10 && COLS == 12)
    {
        return "Hard";
    }
    else if (ROWS == 10 && COLS == 12)
    {
        return "Holy Shit";
    }
    else
        return "Invalid difficulty";
}