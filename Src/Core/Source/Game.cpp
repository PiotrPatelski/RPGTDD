
#include <Game.h>

namespace Core
{

Game::Game(IEngineContext& engineContext)
:   IGame::IGame(),
    window{engineContext.getWindow()},
    clock{engineContext.getClock()},
    stateMachine{engineContext.getStateMachine()},
    graphicsConfig{engineContext.getGraphicsConfig()}
{}

void Game::applyGraphicsSettings()
{
    IniParser parser(binaryPath);
    graphicsConfig.fetchSettingsFromFile(parser);
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
