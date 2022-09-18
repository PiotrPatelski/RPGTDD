#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <WindowManager.h>

namespace Core
{

class IGame
{
public:
    IGame(){}
    virtual ~IGame(){}

    virtual bool isWindowActive() = 0;

    virtual void update() = 0;
    virtual void updateDeltaTime() = 0;
    virtual void render() = 0;
private:
};

class Game : public IGame
{
public:
    Game(IWindowManager&);
    virtual ~Game(){}

    virtual bool isWindowActive(){return windowMngr.isWindowActive();}

    virtual void update();
    virtual void updateDeltaTime();
    virtual void render();
private:
    IWindowManager& windowMngr;

};


}