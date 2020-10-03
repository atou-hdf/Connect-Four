#include "../include/game.h"
#include "../include/textureManager.h"
#include "../include/gameObject.h"
#include "../include/map.h"
#include "../include/board.h"
#include <windows.h>

// game mode : with friend / against AI
static const int FRIEND = 1;
static const int AI = 2;
// game turn : Human / AI
static const int BTURN = 0;
static const int RTURN = 1;
// game winner : Red / Black
static const int W_RED = 1;
static const int W_BLACK = 2;

// define game objects
GameObject* gameMenu;
GameObject* friendMenu;
GameObject* aiMenu;
GameObject* gameBoard;
GameObject* red_piece;
GameObject* black_wins;
GameObject* red_wins;
GameObject* black_turn;
GameObject* red_turn;
GameObject* exit_game;
GameObject* restart;

// define map
Map* map;
SDL_Renderer* Game::renderer = NULL;

// mouse controller
Mouse *mouse;



Game::Game()
{

}

Game::~Game()
{

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if( SDL_Init(SDL_INIT_EVERYTHING) == 0 )
    {
        std::cout << "Subsystems Initialised"<< std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window)
        {
            std::cout << "Window created" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created" << std::endl;
        }
        isRunning = true;
    }
    mouse = new Mouse();
    gameMenu = new GameObject("images/menu.png", 0, 0, false);
    friendMenu = new GameObject("images/menu_friend.png", 0, 0, true);
    aiMenu = new GameObject("images/menu_ai.png", 0, 0, true);
    gameBoard = new GameObject("images/game.png", 0, 0, true);
    black_wins = new GameObject("images/black_wins.png", 0, 0, true);
    red_wins = new GameObject("images/red_wins.png", 0, 0, true);
    black_turn = new GameObject("images/black_turn.png", 0, 0, true);
    red_turn = new GameObject("images/red_turn.png", 0, 0, true);
    exit_game = new GameObject("images/exit.png", 0, 0, true);
    restart = new GameObject("images/restart.png", 0, 0, true);
    map = new Map(0,0);
}

void Game::handleEvents()
{
    int choice = 0;

    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT:
            isRunning = false;
            break;

        case SDL_MOUSEBUTTONUP :
            if( !gameMenu->isfree() )
            {
                gameMenu->updateOnClick(&choice);
                map->gameMode(choice);
            }
            break;
        case SDL_MOUSEBUTTONDOWN :
            if( !map->getGameOver() && gameMenu->isfree() )
            {
                switch( map->getMode() )
                {
                case 1 :
                    if( gameMenu->isfree() && !map->getGameOver() )
                        map->update();
                    break;
                case 2 :
                    if( map->getTurn() == BTURN)
                    {
                        map->playerMove(BLACK);
                    }
                    break;
                default :
                    break;
                }
            }
            if(mouse->inRestart())
            {
                map->updateBoard();
                map->setTurn(0);
                if( map->getGameOver() == true )
                    map->setGameOver(false);
            }
            if( mouse->inExit() )
            {
                isRunning = false;
            }
            break;

        default:
            break;
    }
    if( !map->getGameOver() && gameMenu->isfree() )
    {
        if( map->getMode() == AI && map->getTurn() == RTURN)
        {
            map->aiMove(RED);
        }
    }

    if( !gameMenu->isfree())
    {
        if(mouse->inFriend())
        {
            friendMenu->setState(false);
        }
        else
            friendMenu->setState(true);

        if(mouse->inAi())
        {
            aiMenu->setState(false);
        }
        else
            aiMenu->setState(true);
    }
    if( gameMenu->isfree() )
    {
        if( mouse->inExit())
            exit_game->setState(false);
        else
            exit_game->setState(true);

        if( mouse->inRestart() )
            restart->setState(false);
        else
            restart->setState(true);
    }
}


void Game::update()
{
    if( gameMenu->isfree() )
    {
        if( !map->getGameOver() )
        {
            if( map->getTurn() == RTURN )
            {
                red_turn->setState(false);
                black_turn->setState(true);
            }
            else if ( map->getTurn() == BTURN )
            {
                red_turn->setState(true);
                black_turn->setState(false);
            }
        }

        if( map->getGameOver() )
        {
            map->isfree();
            if(map->getWinner() == W_RED)
            {
                red_wins->setState(false);
                black_wins->setState(true);
            }
            else if(map->getWinner() == W_BLACK)
            {
                red_wins->setState(true);
                black_wins->setState(false);
            }
        }
    }


    if( !gameMenu->isfree() )
    {
        gameMenu->update();
        friendMenu->update();
        aiMenu->update();
    }
    else if( gameMenu->isfree())
    {
        gameBoard->setState(false);
        gameBoard->update();
        black_turn->update();
        red_turn->update();
        exit_game->update();
        restart->update();

        if( map->getGameOver())
        {
            map->setGameOver(true);
            black_turn->setState(true);
            red_turn->setState(true);
            black_wins->update();
            red_wins->update();
        }
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    //
    if(!gameMenu->isfree())
    {
        gameMenu->render();
        friendMenu->render();
        aiMenu->render();

    }
    if(!gameBoard->isfree())
    {
        gameBoard->render();
    }
    if( gameMenu->isfree())
    {
        map->drawMap();
        black_turn->render();
        red_turn->render();
        exit_game->render();
        restart->render();

        if( map->getGameOver())
        {
            black_wins->render();
            red_wins->render();
        }
    }
    //
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}
