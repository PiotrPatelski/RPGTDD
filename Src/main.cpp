#include <GameLoop.h>
#include <Game.h>
#include <Clock.h>
#include <StateMachine.h>
#include <iostream>


int main()
{
    std::cout<<"Entered main.cpp..."<<std::endl;
    Core::Window window;
    Core::Clock clock;
    Core::StateMachine stateMachine;
    Core::Game sfmlRpg(window, clock, stateMachine);
    Core::GameLoop gameInstance(sfmlRpg);
    gameInstance.run();

    return 0;
}