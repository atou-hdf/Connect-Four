#include "../include/map.h"
#include "../include/textureManager.h"
#include <vector>
#include <Windows.h>
#define DEPTH 5


int game_array_y[6] = { 164, 215, 267, 315, 366, 417};
int game_array_x[7] = { 226, 275, 326, 376, 425, 476, 526};


Map::Map()
{

    black = TextureManager::LoadTexture("images/black.png");
    red = TextureManager::LoadTexture("images/red.png");
    white = TextureManager::LoadTexture("images/white.png");

    src.x = src.y = 0;
    src.w  = 128;
    src.h  = 128;
    dest.w  = 43;
    dest.h  = 43;

    mode = 0;

    dest.x = dest.y = 0;
    std::cout << "Map created sucsesfully"<<std::endl;

}

Map::Map(int x, int y):mouse(x,y)
{
    black = TextureManager::LoadTexture("images/black.png");
    red = TextureManager::LoadTexture("images/red.png");
    white = TextureManager::LoadTexture("images/white.png");

    src.x = src.y = 0;
    src.w  = 128;
    src.h  = 128;
    dest.w  = 43;
    dest.h  = 43;

    mode = 0;

    dest.x = dest.y = 0;
    std::cout << "Map created sucsesfully"<<std::endl;
}

void Map::drawMap()
{
    char type = EMPTY;
    for( int row = 0; row < 6; row++)
    {
        for( int col = 0; col < 7; col++)
        {
            type = board.getBoard(row,col);

            dest.x = game_array_x[col];
            dest.y = game_array_y[row];

            switch(type)
            {
            case EMPTY:
                TextureManager::draw(white, src, dest);
                break;
            case BLACK:
                TextureManager::draw(black, src, dest);
                break;
            case RED:
                TextureManager::draw(red, src, dest);
                break;
            default:
                break;
            }
        }
    }
}

void Map::update()
{
    switch(turn%2)
    {
    case 0:
        playerMove(BLACK);
        break;
    case 1:
        playerMove(RED);
        break;
    default:
        break;
    }
}

void Map::playerMove(char piece)
{
    switch (mouse.inColumn())
    {
    case 0:
        incTurn(0);
        board.setBoard(0,piece);
        updateGameOver(0);
        break;
    case 1:
        incTurn(1);
        board.setBoard(1,piece);
        updateGameOver(1);
        break;
    case 2:
        incTurn(2);
        board.setBoard(2,piece);
        updateGameOver(2);
        break;
    case 3:
        incTurn(3);
        board.setBoard(3,piece);
        updateGameOver(3);
        break;
    case 4:
        incTurn(4);
        board.setBoard(4,piece);
        updateGameOver(4);
        break;
    case 5:
        incTurn(5);
        board.setBoard(5,piece);
        updateGameOver(5);
        break;
    case 6:
        incTurn(6);
        board.setBoard(6,piece);
        updateGameOver(6);
        break;
    default:
        break;
    }
}

void Map::aiMove(char piece)
{
    int start = 0;
    node move;
    Ai ai;

    for (int col = 0; col < COLS; col++)
    {
        if (board.is_legal(col)) {
            start = col;
            break;
        }
    }

    do
    {
        //std::cout << "In map before alphabeta ! " << std::endl;
        move = ai.alphabeta(board,DEPTH,M_INF,P_INF,true, start);
        std::cout << "playing : " << move.column << " with value : " << move.value << std::endl;
        incTurn(move.column);

    } while ( !board.make_move(move.column,RED) );
    updateGameOver(move.column);
    

}

void Map::updateGameOver(int move)
{
    game_over = board.is_winner(move);
    if( game_over )
        winner = turn%2 + 1;
    else {
        int full = 0;
        for (int i = 0; i < COLS; i++) {
            if (!board.is_legal(i)) {
                full++;
            }
            else {
                break;
            }
        }
        if (full == COLS) {
            game_over = true;
            winner = 3;
        }
    }
}

bool Map::getGameOver()
{
    return game_over;
}

void Map::incTurn(int move)
{
    if (board.is_legal(move))
        //std::cout << "Board is legal" << std::endl;
        turn++;
}

bool Map::isfree()
{
    if(game_over)
        return true;
    else
        return false;
}


void Map::gameMode(int choice)
{
    mode = choice;
}
