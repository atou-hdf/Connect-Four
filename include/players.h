#ifndef PLAYERS_H_INCLUDED
#define PLAYERS_H_INCLUDED
#include "board.h"

class Ai
{
private:
    char game_piece;
public:
    Ai(){ game_piece = ' ';};                                              // BLACK ou RED
    int alphabeta(Board& b, int depth, int alpha, int beta, bool is_ai, int& best_move, int* exp_alphabeta);
};


#endif // PLAYERS_H_INCLUDED
