#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED
#include "game.h"

class GameObject
{
public:
    GameObject(const char* texturesheet, int x, int y, bool state);
    ~GameObject(){ }

    void update();
    void render();
    void freeObject();
    bool isfree() const { return free; };
    void setState(bool state);
    void updateOnClick(int *choice);
    void updateOnHover();

private:
    int xpos;
    int ypos;
    bool free;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;

};

#endif // GAMEOBJECT_H_INCLUDED
