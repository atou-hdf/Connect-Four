#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <iostream>
#include <vector>
#include "game.h"

static const int ROWS = 6;
static const int COLS = 7;
static const char RED = 'R';
static const char BLACK = 'B';
static const char EMPTY = ' ';
static const int P_INF = 1000000;
static const int M_INF= -1000000;

class Board
{
    private :
        std::vector< std::vector<char> > game_board;
        friend class Map;
    public :
        Board();
        char getBoard(int row, int col);
        bool setBoard(int col, char piece);
        void new_board();
        //void display();
        bool is_legal(const int col) const;
        bool make_move(const int col, const char piece);
        int save_move(const int col);
        bool is_winner_horiz(const int col);
        bool is_winner_vert(const int col);
        bool is_winner_diag_left(const int col);
        bool is_winner_diag_right(const int col);
        bool is_winner(const int col);
        bool winning_move(const char piece);
        bool is_draw();
        int evaluate_window( const std::vector<char> window, const char piece );
        int horiz_score( const std::vector<char>, char );
        int vert_score( const std::vector<char>, char );
        int diag_right_score( const char piece );
        int diag_left_score( const char piece );
        int score( const char piece );
        void emptying(const int move, const int col);

};

#endif // BOARD_H_INCLUDED
