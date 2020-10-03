#include "../include/mouseController.h"



Mouse::Mouse()
{
    xpos = 0;
    ypos = 0;

    game_column[0][0] = 225;
    game_column[0][1] = game_column[0][0]+42;
    for(int i = 1; i<7; i++)
    {
        game_column[i][0] = game_column[i-1][0] + 50;
        game_column[i][1] = game_column[i][0] + 42;
    }
}

Mouse::Mouse(int x, int y )
{
    xpos = x;
    ypos = y;

    game_column[0][0] = 225;
    game_column[0][1] = game_column[0][0]+42;
    for(int i = 1; i<7; i++)
    {
        game_column[i][0] = game_column[i-1][0] + 50;
        game_column[i][1] = game_column[i][0] + 42;
    }
}

int Mouse::inColumn()
{
    SDL_GetMouseState( &xpos, &ypos);

    for(int i = 0; i < 7; i++)
    {
        if( xpos > game_column[i][0] && xpos < game_column[i][1] && ypos > 164 && ypos < 460)
        {
            return i;
            break;
        }
    }
    return 8;
}

bool Mouse::inFriend()
{
    SDL_GetMouseState( &xpos, &ypos);
    if( xpos > 166 && xpos < 351 && ypos > 403 && ypos < 445)
    {
        return true;
    }
    else
        return false;
}

bool Mouse::inAi()
{
    SDL_GetMouseState( &xpos, &ypos);
    if( xpos > 450 && xpos < 634 && ypos > 405 && ypos < 447)
    {
        return true;
    }
    else
        return false;
}

bool Mouse::inExit()
{
    SDL_GetMouseState( &xpos, &ypos);
    if( xpos > 659 && xpos < 749 && ypos > 527 && ypos < 569)
    {
        return true;
    }
    else
        return false;
}

bool Mouse::inRestart()
{
    SDL_GetMouseState( &xpos, &ypos);
    if( xpos > 52 && xpos < 143 && ypos > 527 && ypos < 569)
    {
        return true;
    }
    else
        return false;
}

void Mouse::setX(int x)
{
    xpos = x;
}

void Mouse::setY(int y)
{
    ypos = y;
}

int Mouse::getX()
{
    SDL_GetMouseState( &xpos, &ypos);
    return xpos;
}

int Mouse::getY()
{
    SDL_GetMouseState( &xpos, &ypos);
    return ypos;
}

void Mouse::updateState()
{
    SDL_GetMouseState( &xpos, &ypos);
}
