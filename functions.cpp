#include <iostream>
#include <cstdlib> // rand
#include <ctime>
#include <fstream>
#include "functions.h"
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