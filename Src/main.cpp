#include <GameLoop.h>
#include <Game.h>
#include <WindowManagerBuilder.h>
#include <iostream>


int main()
{
    std::cout<<"Entered main.cpp..."<<std::endl;
    auto windowBuilder = std::make_unique<Core::WindowManagerBuilder>();
    std::unique_ptr<Core::IWindowManager> windowMngr = windowBuilder->build();
    Core::Game sfmlRpg(*windowMngr.release());
    Core::GameLoop gameInstance(sfmlRpg);
    gameInstance.run();

    return 0;
}