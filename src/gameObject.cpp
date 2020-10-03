#include "../include/gameObject.h"
#include "../include/textureManager.h"
#include "../include/mouseController.h"

GameObject::GameObject(const char* texturesheet, int x, int y, bool state)
{
    objTexture = TextureManager::LoadTexture(texturesheet);

    xpos = x;
    ypos = y;
    setState(state);
}

void GameObject::update()
{
    if( !free )
    {
        srcRect.h = 600;
        srcRect.w = 800;
        srcRect.x = 0;
        srcRect.y = 0;

        destRect.x = xpos;
        destRect.y = ypos;
        destRect.w = srcRect.w ;
        destRect.h = srcRect.h ;
    }

}

void GameObject::updateOnClick(int *choice)
{
    Mouse mouse;
    if(mouse.inFriend())
    {
        (*choice) = 1;
        free = true;
    }
    else if(mouse.inAi())
    {
        (*choice) = 2;
        free = true;
    }
}

void GameObject::render()
{
    if( !free )
        SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

void GameObject::freeObject()
{
    free = true;
}

void GameObject::setState(bool state)
{
    free = state;
}
