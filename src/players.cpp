#include <Windows.h>
#include <iostream>
#include "../include/players.h"
#include "../include/board.h"
#include "../include/mouseController.h"


int Ai::alphabeta(Board& b, int depth, int alpha, int beta, bool is_ai, int& best_move, int* exp_alphabeta)
{
    int savemove;
    if ( b.is_draw() ){
        (*exp_alphabeta)++;
        return 0;
    }
    else if ( b.winning_move(BLACK) ){
        (*exp_alphabeta)++;
        return M_INF;
    }
    else if (b.winning_move(RED)) {
        (*exp_alphabeta)++;
        return P_INF;
    }

    if ( depth == 0 ){
        (*exp_alphabeta)++;
        return ( (is_ai) ? b.score(RED) : b.score(BLACK) );
    }

    if ( is_ai )
    {
        int best_value = M_INF;
        for ( int col = 0; col < COLS; col++ )
        {
          if ( b.is_legal(col) )
          {
            savemove = b.save_move(col);
            b.make_move(col,RED);
            int value = alphabeta(b,depth-1,alpha,beta,!is_ai,best_move,exp_alphabeta);
            if ( value > best_value )
            {
              best_value = value;
              best_move = col;
            }
            b.emptying(savemove,col);
            alpha = (std::max)(alpha,value);
            if( beta <= alpha )
                break;
          }
        }
        return best_value;
    }
    else
    {
        int best_value = P_INF;
        for ( int col = 0; col < COLS; ++col )
        {
          if ( b.is_legal(col) )
          {
            savemove = b.save_move(col);
            b.make_move(col,BLACK);
            int value = alphabeta(b,depth-1,alpha,beta,!is_ai,best_move,exp_alphabeta);
            if ( value < best_value )
            {
              best_value = value;
            }
            b.emptying(savemove,col);
            beta = (std::min)(beta,value);
            if( beta <= alpha)
                break;
          }
        }
        return best_value;
    }
}

