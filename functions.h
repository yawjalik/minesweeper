#ifndef FUNCTIONS_H
#define FUNCTIONS_H

const int ROWS = 5;  // max row
const int COLS = 5;  // max col

void initialize_map(char[][COLS]);
void print_map(char[][COLS]);
void generate_mines(char[][COLS]);
void generate_clues(char[][COLS]);
void flag(char[][COLS]);

#endif