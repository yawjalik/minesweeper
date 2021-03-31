#include <iostream>
#include <string>
#include <limits> // for the std::limits thing
#include "functions.h"
using namespace std;

int main()
{
    char map[ROWS][COLS];

    // main menu
    string input;
    system("clear");
    // to handle the cin cout problem, where it takes "Minesweeper!" into cin
    bool started = false;
    while (true)
    {
        // Print main menu and get input:
        if (started)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Minesweeper!" << endl;
        cout << "1. New Game  " << "2. Load Game  " << "3. Quit" << endl;
        cout << ">> ";
        getline(cin, input);

        if (input == "1")
        {
            // Game loop
            int row, col;
            initialize_map(map);
            generate_mines(map);
            started = true;

            while (true)
            {
                system("clear");
                print_map(map);
                cin >> row >> col;  // Change to something like a0, b1, etc.

                if (row > ROWS-1 || col > COLS-1)
                {
                    continue;
                }

                if (map[row][col] == 'X')
                {
                    // print_uncovered_map()
                    cout << "Game Over!\n" << endl;
                    break;
                }

                // if (some winning condition)
                // {
                //     // print_uncovered_map()
                //     cout << "you win or whatever" << endl;
                //     break;
                // }
                map[row][col] = 'O'; // keeping track of the squares clicked / uncovered
            }
        }
        else if (input == "3")
        {
            cout << "Exited" << endl;
            break;
        }
        else
        {
            started = false;
            cout << endl;
        }

    }

    return 0;
}


