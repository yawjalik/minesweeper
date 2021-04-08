#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void initialize_board(char **, int, int, char);
bool load_board(char **&, char **&, int &, int &, int &, int &);
void print_board(char **, int, int);
void print_instructions();
int generate_mines(char **, int, int);
void generate_clues(char **, int, int);
void delete_board(char **, int);
bool save_board(char **, char**, int, int, int, int);

#endif