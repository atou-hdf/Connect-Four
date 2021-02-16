#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include <vector>
#include <iostream>
#include "mouseController.h"
#include "board.h"
#include "players.h"
#include "game.h"


class Map{
public:
    Map();
    Map(int x, int y);
    ~Map() {
        SDL_DestroyTexture(red);
        SDL_DestroyTexture(white);
        SDL_DestroyTexture(black);
    };

    void drawMap();

    void update();
    void aiMove(char piece);
    void playerMove(char piece);
    void gameMode(int choice);
    void incTurn(int move);
    int getWinner() { return winner; }
    void updateGameOver(int move);
    void setGameOver(bool state) { game_over = state ;}
    bool getGameOver();
    bool isfree();
    int getMode() { return mode; }
    int getTurn() { return turn%2; }
    void setTurn(int t) { turn = 0;}
    void updateBoard() { board.new_board(); }


private:

    SDL_Rect src, dest;
    SDL_Texture* red;
    SDL_Texture* white;
    SDL_Texture* black;

    Board board;
    int mode ;
    int turn = 0;
    int winner = 0;
    bool game_over = false;
    Mouse mouse;

};



#endif // MAP_H_INCLUDED
