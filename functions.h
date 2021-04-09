#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void initialize_board(char **, int, int, char);
bool load_board(char **&, char **&, int &, int &, int &, int &);
void select_difficulty(char &, int &, int &);
int generate_mines(char **, int, int, int, int);
void generate_clues(char **, int, int);
void delete_board(char **, int);
bool save_board(char **, char **, int, int, int, int);
void flood_fill(char **, char **, int, int, int, int, int &);
void game_loop(char **, char **, int, int, int, int, bool &, bool &, char);

#endif