
#include <Game.h>

namespace Core
{

Game::Game(IWindowManager& windowMngr)
:   IGame::IGame(),
    windowMngr{windowMngr}
{

}

void Game::update()
{

}

void Game::updateDeltaTime()
{

}

void Game::render()
{
    windowMngr.clearWindow();
    windowMngr.displayWindow();
}

}
