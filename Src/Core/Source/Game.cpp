
#include <Game.h>

namespace Core
{

Game::Game(std::unique_ptr<IEngine> engine)
:   IGame::IGame(),
    engine(std::move(engine))
{}

void Game::fetchGraphicsSettings(IIniParser& parser)
{
    parser.parseFileTo(engine->getGraphicsConfig());
}

void Game::fetchPlayerInputSettings(IIniParser& parser)
{
    parser.parseFileTo(engine->getKeyboardConfig().supportedKeys);
}

void Game::startStateMachine()
{
    engine->runInitialState();
}

void Game::openWindow()
{
    engine->launchWindow();
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
