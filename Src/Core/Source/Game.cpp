
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

void Game::startStateMachine()
{
    stateMachine.runState(std::make_unique<States::State>());
}

void Game::update()
{
    window.handleSfmlEvents(sfmlEvent);
    if(not stateMachine.isWorkDone())
        stateMachine.update(window.isCurrentlyFocused(), clock.getDeltaTime());
    else
        window.close();
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
