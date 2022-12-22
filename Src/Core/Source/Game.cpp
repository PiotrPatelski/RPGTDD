
#include <Game.h>

namespace Core
{

Game::Game(std::unique_ptr<IEngine> engine)
:   IGame::IGame(),
    engine(std::move(engine)),
    config(std::make_shared<Config>())
{
    IniParser parser;
    fetchGraphicsSettings(parser);
    fetchPlayerInputSettings(parser);
}

void Game::fetchGraphicsSettings(IIniParser& parser)
{
    config->graphics = parser.parseGraphicsConfig();
}

void Game::fetchPlayerInputSettings(IIniParser& parser)
{
    config->keyboard.supportedKeys = parser.parseKeyboardConfig();
}

void Game::startStateMachine()
{
    engine->runInitialState(config);
}

void Game::openWindow()
{
    engine->launchWindow(config);
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
