#include <GameLoop.h>
#include <Game.h>
#include <Clock.h>
#include <StateMachine.h>
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout<<"Entered main.cpp..."<<std::endl;

    std::string argv_str(argv[0]);
    auto binaryPath = argv_str.substr(0, argv_str.find_last_of("/"));
    std::cout<<"Binary path: "<< binaryPath << std::endl;
    auto buildPath = binaryPath + "/../";
    std::cout<<"Build path: "<< buildPath << std::endl;

    Core::EngineContext engineContext;
    Core::Game sfmlRpg(engineContext);
    sfmlRpg.setBuildPath(buildPath);
    Core::GameLoop gameInstance(sfmlRpg);
    gameInstance.run();

    return 0;
}