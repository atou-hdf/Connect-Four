#include <Windows.h>
#include <iostream>
#include "../include/players.h"
#include "../include/board.h"
#include "../include/mouseController.h"


node Ai::alphabeta(Board& b, int depth, int alpha, int beta, bool is_ai, int last_move)
{
    int savemove;
    node bestPlay;

    if ( b.is_draw() ){
        bestPlay.column = last_move;
        bestPlay.value = 0;
        return bestPlay;
    }
    else if ( b.winning_move(BLACK) ){
        bestPlay.column = last_move;
        bestPlay.value = M_INF;
        return bestPlay;
    }
    else if (b.winning_move(RED)) {
        bestPlay.column = last_move;
        bestPlay.value = P_INF;
        return bestPlay;
    }
    else if ( depth == 0 ){
        return heurFunction(b, is_ai, last_move);
    }
    if ( is_ai )
    {
        int best_value = M_INF;
        bestPlay.column = last_move;
        bestPlay.value = best_value;
        
        for ( int col = 0; col < COLS; col++ )
        {
            if ( b.is_legal(col) )
            {
                
                savemove = b.save_move(col);
                b.make_move(col,RED);
                node play = alphabeta(b,depth-1,alpha,beta,false, col);
                int value = play.value;
                if ( value > best_value )
                {
                    best_value = value;
                    bestPlay.column = col;
                    bestPlay.value = best_value;
                }
            
                b.emptying(savemove, col);
                alpha = (std::max)(alpha, best_value);
                if (beta <= alpha){
                    return bestPlay;
                }
            }
          
        }
        return bestPlay;
    }
    else
    {
        int best_value = P_INF;
        bestPlay.column = last_move;
        bestPlay.value = best_value;
        
        for ( int col = 0; col < COLS; col++)
        {
            if ( b.is_legal(col) )
            {
                savemove = b.save_move(col);
                b.make_move(col,BLACK);
                node play = alphabeta(b, depth - 1, alpha, beta, true, col);
                int value = play.value;
                if ( value < best_value )
                {
                    best_value = value;
                    bestPlay.column = col;
                    bestPlay.value = best_value;
                }
                b.emptying(savemove, col);
                beta = (std::min)(beta, best_value);
                if (beta <= alpha)
                    return bestPlay;
            }
        }
        return bestPlay;
    }
}

node Ai::heurFunction(Board& b, bool is_ai, int last_move) {
    node bestPlay;
    bestPlay.column = last_move;
    bestPlay.value = ((is_ai) ? b.score(BLACK) : b.score(RED));
    return bestPlay;
}