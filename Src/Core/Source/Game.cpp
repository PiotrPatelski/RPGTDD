
#include <Game.h>

namespace Core
{

Game::Game(IEngineContext& engineContext)
:   IGame::IGame(),
    window{engineContext.getWindow()},
    clock{engineContext.getClock()},
    stateMachine{engineContext.getStateMachine()},
    graphicsConfig{engineContext.getGraphicsConfig()},
    keyboardConfig{engineContext.getKeyboardConfig()}
{}

void Game::fetchGraphicsSettings(IIniParser& parser)
{
    parser.parseFileTo(graphicsConfig);
}

void Game::fetchPlayerInputSettings(IIniParser& parser)
{
    parser.parseFileTo(keyboardConfig);
}

void Game::startStateMachine()
{
    stateMachine.runState(std::make_unique<States::MainMenuState>());
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
