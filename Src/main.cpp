#include <GameLoop.h>
#include <Game.h>
#include <WindowManagerBuilder.h>
#include <iostream>


int main()
{
    std::cout<<"Entered main.cpp..."<<std::endl;
    auto windowMngr = Core::WindowManagerBuilder{}.build();
    Core::Game sfmlRpg(windowMngr);
    Core::GameLoop gameInstance(sfmlRpg);
    gameInstance.run();

    return 0;
}