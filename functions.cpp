/* 
MINESWEEPER!!!
Group 19: YAW Jalik, GUILLEMOT Raphaele Michelle
Description: functions.cpp holds the helper functions for easy read and run logic flow
*/

#include <iostream>
#include <cctype>
#include <string>
#include "functions.h"
using namespace std;

bool is_2digit_coord(string input)
{
    // condition: 3 character inputs, both lower letters and digits like a10
    return (input.length() == 3 && islower(input[0]) && isdigit(input[1]) && isdigit(input[2]));
}

bool is_1digit_coord(string input)
{
    // condition: 2 character inputs, both lower letters and digits like a1
    return (input.length() == 2 && islower(input[0]) && isdigit(input[1]));
}

bool is_2digit_flag(string input)
{
    // condition: 4 character inputs, first a ? then both lower letters and digits like ?a10
    return (input.length() == 4 && input[0] == '?' && islower(input[1]) && isdigit(input[2]) && isdigit(input[3]));
}

bool is_1digit_flag(string input)
{
    // condition: 3 character inputs, first a ? then both lower letters and digits like ?a1
    return (input.length() == 3 && input[0] == '?' && islower(input[1]) && isdigit(input[2]));
}

void delete_board(char **board, int ROWS)
{
    for (int i = 0; i < ROWS; i++)
    {
        delete[] board[i];
    }
    delete[] board;
}

void clear_screen() // Clearing screen https://stackoverflow.com/questions/5367068/clear-a-terminal-screen-for-real
{
    cout << "\033[H\033[J";
}
