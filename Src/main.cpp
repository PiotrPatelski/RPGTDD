#include <GameLoop.h>
#include <Game.h>
#include <Clock.h>
#include <StateMachine.h>
#include <iostream>


int main()
{
    std::cout<<"Entered main.cpp..."<<std::endl;
    Core::EngineContext engineContext;
    Core::Game sfmlRpg(engineContext);
    Core::GameLoop gameInstance(sfmlRpg);
    gameInstance.run();

    return 0;
}