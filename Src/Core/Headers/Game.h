#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace Core
{

class IGame
{
public:
    IGame(){}
    virtual ~IGame(){}

    virtual bool getIsRunning() = 0;

    virtual void setIsRunning(bool value) = 0;

    virtual void update() = 0;
private:
};

class Game : public IGame
{
public:
    Game(){}
    virtual ~Game(){}

    virtual bool getIsRunning(){return isRunning;}

    virtual void setIsRunning(bool value){isRunning = value;}

    virtual void update();

private:
    bool isRunning{false};

};


}