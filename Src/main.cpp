#include <GameLoop.h>
#include <Game.h>
#include <CoreBuilder.h>
#include <StateMachine.h>
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout<<"Entered main.cpp..."<<std::endl;
    Core::Game sfmlRpg(std::make_unique<Core::Engine>(Core::CoreBuilder{}));
    Core::GameLoop gameInstance(sfmlRpg);
    gameInstance.run();

    return 0;
}