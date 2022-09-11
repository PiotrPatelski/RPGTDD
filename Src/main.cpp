#include <GameLoop.h>
#include <iostream>


int main()
{
    std::cout<<"Entered main.cpp..."<<std::endl;
    Core::Game sfmlRpg;
    Core::GameLoop gameInstance(sfmlRpg);
    gameInstance.run();

    return 0;
}