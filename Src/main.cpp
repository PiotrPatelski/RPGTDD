#include <GameLoop.h>
#include <Game.h>
#include <WindowBuilder.h>
#include <Clock.h>
#include <iostream>


int main()
{
    std::cout<<"Entered main.cpp..."<<std::endl;
    auto window = Core::WindowBuilder{}.build();
    Core::Clock clock;
    Core::Game sfmlRpg(window, clock);
    Core::GameLoop gameInstance(sfmlRpg);
    gameInstance.run();

    return 0;
}