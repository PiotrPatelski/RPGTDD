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
    if(game.getIsRunning())
    {
        game.update();
    }
}

}
