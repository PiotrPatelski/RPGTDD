#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Window.h>
#include <Clock.h>
#include <StateMachine.h>

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
    Game(IWindow&, IClock&, IStateMachine&);
    virtual ~Game(){}

    virtual bool isWindowActive(){return window.isActive();}

    virtual void update();
    virtual void updateDeltaTime();
    virtual void render();
private:
    IWindow& window;
    IClock& clock;
    IStateMachine& stateMachine;

    sf::Event sfmlEvent;

};


}