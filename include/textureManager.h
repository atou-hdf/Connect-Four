#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED
#include "game.h"

class TextureManager
{
public:
    static SDL_Texture* LoadTexture(const char* filename);
    static void draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
};


#endif // TEXTUREMANAGER_H_INCLUDED
