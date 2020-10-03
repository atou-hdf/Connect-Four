#ifndef MOUSECONTROLLER_H_INCLUDED
#define MOUSECONTROLLER_H_INCLUDED
#include "game.h"

class Mouse
{
    int xpos;
    int ypos;
    int game_column[7][2];
public:
    Mouse();
    Mouse(int x, int y);

    void setX(int x);
    void setY(int y);
    int inColumn();
    bool inFriend();
    bool inAi();
    bool inExit();
    bool inRestart();
    int getX();
    int getY();
    void updateState();
};

#endif // MOUSECONTROLLER_H_INCLUDED
