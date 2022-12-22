#include <GameLoop.h>

namespace Core
{

GameLoop::GameLoop(IGame& game)
: game(game)
{
    std::cout << "GameLoop has set a game instance..." << std::endl;
}

void GameLoop::run()
{
    std::cout << "Starting game instance..." << std::endl;

    game.startStateMachine();
    game.openWindow();
    try
    {
        while(game.isWindowOpen())
        {
            game.updateClock();
            game.update();
            game.render();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "UNEXPECTED EXCEPTION APPEARED: "<< e.what() << '\n';
    }
}

}
