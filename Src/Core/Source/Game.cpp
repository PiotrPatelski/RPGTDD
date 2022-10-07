
#include <Game.h>

namespace Core
{

Game::Game(IWindow& window, IClock& clock, IStateMachine& stateMachine)
:   IGame::IGame(),
    window{window},
    clock{clock},
    stateMachine{stateMachine}
{

}

void Game::update()
{
    window.handleSfmlEvents(sfmlEvent);
    stateMachine.update(window.isCurrentlyFocused(), clock.getDeltaTime());
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
