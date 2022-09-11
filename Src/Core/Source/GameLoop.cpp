#include <GameLoop.h>

namespace Core
{

GameLoop::GameLoop(IGame& game)
: IGameLoop::IGameLoop(game),
  game(game)
{

}

void GameLoop::run()
{
    while(game.getIsRunning())
    {
        game.update();
        game.updateDeltaTime();
        game.render();
    }
}

}
