#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Window.h>
#include <Clock.h>
#include <StateMachine.h>
#include <EngineContext.h>

namespace Core
{

class IGame
{
public:
    IGame(){}
    virtual ~IGame(){}

    virtual bool isWindowOpen() = 0;

    virtual void startStateMachine() = 0;
    virtual void openWindow() = 0;

    virtual void update() = 0;
    virtual void updateDeltaTime() = 0;
    virtual void render() = 0;
private:
};

class Game : public IGame
{
public:
    Game(IEngineContext&);
    virtual ~Game(){}

    virtual bool isWindowOpen() override {return window.isActive();}

    virtual void startStateMachine() override;
    virtual void openWindow() override {window.open();}

    virtual void update() override;
    virtual void updateDeltaTime() override;
    virtual void render() override;
private:
    IWindow& window;
    IClock& clock;
    IStateMachine& stateMachine;

    sf::Event sfmlEvent;

};


}