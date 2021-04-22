#include <iostream>
#include <string>
#include "prints.h"
using namespace std;

void print_title()
{
    cout << "█▀▄▀█  ▀  █▀▀▄ █▀▀ █▀▀ █   █ █▀▀ █▀▀ █▀▀█ █▀▀ █▀▀█" << endl;
    cout << "█ ▀ █ ▀█▀ █  █ █▀▀ ▀▀█ █▄█▄█ █▀▀ █▀▀ █  █ █▀▀ █▄▄▀" << endl;
    cout << "▀   ▀ ▀▀▀ ▀  ▀ ▀▀▀ ▀▀▀  ▀ ▀  ▀▀▀ ▀▀▀ █▀▀▀ ▀▀▀ ▀ ▀▀" << endl;
    cout << "\n0. Instructions   1. New Game   2. Load Game   3. Quit" << endl;
    cout << ">> ";
}

void print_instructions()
{
    cout << "█ █▄ █ █▀ ▀█▀ █▀█ █ █ █▀▀ ▀█▀ █ █▀█ █▄ █ █▀" << endl;
    cout << "█ █ ▀█ ▄█  █  █▀▄ █▄█ █▄▄  █  █ █▄█ █ ▀█ ▄█\n" << endl;
    string input;
    cout << "WIN by uncovering all the empty tiles \nLOSE by stepping on an armed mine \n \n";

    cout << "Each tile will have a number indicating how many BOMBS are around it \n e.g. a tile with the number 2 indicates that there are 2 mines next to it \n \n";

    cout << "UNCOVER by typing in the coordinates of the tile \n e.g. >> a0 \n \n";

    cout << "add and remove FLAGS with '?' to note down possible armed locations and prevent tripping them \n e.g. >> ?a0 \n \n";

    cout << "Type 'save' during gameplay to save your progress\n \n";

    cout << "Type 'quit' or 'exit' during gameplay to quit (No autosaves)\n \n";

    cout << "Enter any value to return to menu" << endl;

    cout << ">> ";
    cin >> input;
}

void print_end()
{
    cout << "█▀▀ █▀█ █▀█ █▀▄ █▄▄ █▄█ █▀▀ █" << endl;
    cout << "█▄█ █▄█ █▄█ █▄▀ █▄█  █  ██▄ ▄" << endl;
}
