
#include <Game.h>

namespace Core
{

Game::Game(IWindow& window, IClock& clock)
:   IGame::IGame(),
    window{window},
    clock{clock}
{

}

void Game::update()
{
    window.handleSfmlEvents(sfmlEvent);
}

void Game::updateDeltaTime()
{
    clock.updateDeltaTime();
}

void Game::render()
{
    window.clear();
    window.displayWindow();
}

}
