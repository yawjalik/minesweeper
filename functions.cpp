#include <iostream>
#include <cstdlib> // rand
#include <ctime>
#include <fstream>
#include "functions.h"
using namespace std;

void initialize_board(char **board, int ROWS, int COLS)
{
    for (int i = 0; i < ROWS; i++)
    {
        board[i] = new char[COLS];
        for (int j = 0; j < COLS; j++)
        {
            board[i][j] = '*';
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

void print_board(char **board, int ROWS, int COLS)  // print a less ugly map please
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

void print_covered_board(char **board, int ROWS, int COLS)
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
            // Added the condition to cover up the bombs
            if (board[i][j] == 'X')
                cout << '*' << ' ';
            else
                cout << board[i][j] << ' ';
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
            count++;
        }
    }
    return total_mines;
}

void generate_clues(char **board, int ROWS, int COLS)
{
    // TODO
}

void flag(char **board, int ROWS, int COLS)
{
    // TODO
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