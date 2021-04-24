#include <iostream>
#include <cctype>
#include <string>
#include "functions.h"
using namespace std;

bool is_2digit_coord(string input)
{
    return (input.length() == 3 && islower(input[0]) && isdigit(input[1]) && isdigit(input[2]));
}

bool is_1digit_coord(string input)
{
    return (input.length() == 2 && islower(input[0]) && isdigit(input[1]));
}

bool is_2digit_flag(string input)
{
    return (input.length() == 4 && input[0] == '?' && islower(input[1]) && isdigit(input[2]) && isdigit(input[3]));
}

bool is_1digit_flag(string input)
{
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

void clear_screen()
{
    cout << "\033[H\033[J";
}
