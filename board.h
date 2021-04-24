#ifndef BOARD_H
#define BOARD_H

struct Board
{
    char **raw_board;
    char **covered_board;

    int ROWS, COLS, total_mines, uncovered;

    Board();
    ~Board();

    void initialize_board();
    void select_difficulty();
    bool load_board(int& previous_time);
    void save_board(int previous_time);
    void print_board(char **board);
    void print_summary(int elapsed_time);
    void generate_mines(int row, int col);
    void generate_clues();
    void flood_fill(int row, int col);

    std::string get_difficulty();
};

#endif