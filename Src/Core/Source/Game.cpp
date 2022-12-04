
#include <Game.h>

namespace Core
{

void createPathForFileManagement(const std::string& seed)
{
    std::string argv_str(seed);
    auto binaryPath = argv_str.substr(0, argv_str.find_last_of("/"));
    std::cout<<"Binary path: "<< binaryPath << std::endl;
    auto buildPath = binaryPath + "/../";
    std::cout<<"Build path: "<< buildPath << std::endl;

    Core::IniParser::setBuildPath(buildPath);
    Core::AssetsManager::setBuildPath(buildPath);
}

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
    engine->runInitialState(std::make_unique<MainMenuAssetsManager>());
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
