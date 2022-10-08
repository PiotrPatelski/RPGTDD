#pragma once

#include <Game.h>

namespace Core
{

class IGameLoop
{
public:
    IGameLoop(){}
    virtual ~IGameLoop(){}
    virtual void run() = 0;
private:

};

class GameLoop : public IGameLoop
{
public:
    GameLoop(IGame& game);
    virtual ~GameLoop(){}
    virtual void run();
private:
    IGame& game;

};

}