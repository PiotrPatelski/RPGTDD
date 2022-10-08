#include <GameLoop.h>

namespace Core
{

GameLoop::GameLoop(IGame& game)
: game(game)
{

}

void GameLoop::run()
{
    game.startStateMachine();
    while(game.isWindowActive())
    {
        game.updateDeltaTime();
        game.update();
        game.render();
    }
}

}
