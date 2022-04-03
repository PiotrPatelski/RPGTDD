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

    virtual void update() = 0;
private:
};

class Game : public IGame
{
public:
    Game(){}
    virtual ~Game(){}

    virtual void update();

private:

};


}