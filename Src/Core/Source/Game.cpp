
#include <Game.hpp>

namespace Core
{

Game::Game(std::unique_ptr<IEngine> engine)
:   IGame::IGame(),
    engine(std::move(engine)),
    config(std::make_shared<ConfigManager>())
{}

void Game::startStateMachine()
{
    engine->runInitialState(config);
}

void Game::openWindow()
{
    engine->launchWindow(config->getGraphics());
}

void Game::update()
{
    if(not engine->updateState())
        engine->closeWindow();
}

void Game::updateClock()
{
    engine->updateDeltaTime();
}

void Game::render()
{
    engine->displayRenderedFrame();
}

}
