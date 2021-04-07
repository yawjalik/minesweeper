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

bool load_board(char **board, int &ROWS, int &COLS)
{
    ifstream fin("savefile.txt");
    if (fin.fail())
        return false;

    fin >> ROWS >> COLS;
    char input;
    for (int i = 0; i < ROWS; i++)
    {
        board[i] = new char[COLS];
        for (int j = 0; j < COLS; j++)
        {
            fin >> board[i][j];
        }
    }
    fin.close();
    return true;
}

void print_board(char **board, int ROWS, int COLS) // print a less ugly map please
{
    cout << "  ";
    for (int i = 0; i < COLS; i++)
        cout << i << ' ';
    cout << endl;

    for (int i = 0; i < ROWS; i++)
    {
        cout << char(i + 'a') << ' ';
        for (int j = 0; j < COLS; j++)
        {
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
}

void print_covered_board(char **coords_uncovered, int ROWS, int COLS)
{
    cout << "  ";
    for (int i = 0; i < COLS; i++)
        cout << i << ' ';
    cout << endl;

    for (int i = 0; i < ROWS; i++)
    {
        cout << char(i + 'a') << ' ';
        for (int j = 0; j < COLS; j++)
        {
            cout << coords_uncovered[i][j] << ' ';
        }
        cout << endl;
    }
}

int generate_mines(char **board, int ROWS, int COLS)
{
    srand(time(NULL));
    int count = 0;
    int total_mines = (ROWS * COLS * 0.15);
    // cout << "Total number of mines: " << total_mines << endl;
    while (count <= total_mines)
    {
        int row = rand() % ROWS;
        int col = rand() % COLS;
        if (board[row][col] != 'X')
        {
            board[row][col] = 'X';
            cout << row << col << endl;
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

                if (row > 0) // check top row
                {
                    if (board[row - 1][col] != 'X') // if not X
                        board[row - 1][col] += 1;
                    if (col > 0 && board[row - 1][col - 1] != 'X') // and if left/right are fine too
                        board[row - 1][col - 1] += 1;
                    if (col < COLS && board[row - 1][col + 1] != 'X')
                        board[row - 1][col + 1] += 1;
                }
                if (row < ROWS - 1) // check bottom row
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

bool save_board(char **board, int ROWS, int COLS)
{
    ofstream fout("savefile2.txt");
    if (fout.fail())
    {
        delete_board(board, ROWS);
        return false;
    }

    // Save ROWS and COLS into the first line
    fout << ROWS << ' ' << COLS << '\n';

    // Save the board
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            fout << board[i][j];
        }
        fout << '\n';
    }
    fout.close();
    cout << "Saved" << endl;
    return true;
}