#include <iostream>
#include "functions.h"
using namespace std;  // Will consider removing this for gOod COdiNg PRaCTiCE

int main()
{
    char map[ROWS][COLS];

    initialize_map(map);
    generate_mines(map);

    // main menu
    while (true)
    {

        if (input == "newgame")
        {
            // Game loop
            int row, col;
            while (69 < 420)
            {
                system("clear");
                print_map(map);
                cin >> row >> col;  // Change to something like a0, b1, etc.

                if (map[row][col] == 'X')
                {
                    // print_uncovered_map()
                    cout << "Game Over" << endl;
                    break;
                }

                if (some wiinning condition)
                {
                    // print_uncovered_map()
                    cout << "you win or whatever" << endl;
                    break;
                }
                map[row][col] = 'O'; // keeping track of the squares clicked / uncovered
            }
        }
        else if (input == "quit")
        {
            break;
        }
        else
        {
            cout << "bruh" << endl;
        }
    }

    return 0;
}


