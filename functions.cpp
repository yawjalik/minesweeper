#include <iostream>
#include <cstdlib> // rand
#include <unistd.h> // for system()
#include <ctime>
#include "functions.h"
using namespace std;

void initialize_map(char map[][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            map[i][j] = '*';
        }
    }
}


void print_map(char map[][COLS])  // print a less ugly map please
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            cout << map[i][j] << ' ';
        }
        cout << endl;
    }
}


void generate_mines(char map[][COLS])
{
    int count = 0;

    srand(time(NULL));

    // count == 3 for 3 mines
    while (count != 3)
    {
        int row = rand() % 5;
        int col = rand() % 5;

        if (map[row][col] == '*')
        {
            map[row][col] = 'X';
            count++;
        }

    }
}


void generate_clues(char map[][COLS])
{
    // TODO
    return;
}

void flag(char[][COLS])
{
    // TODO
    return;
}