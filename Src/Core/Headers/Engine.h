#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Window.h>
#include <Clock.h>
#include <StateMachine.h>
#include <Config.h>

namespace Core
{

class IEngine
{
public:
    IEngine(){}
    virtual ~IEngine(){}
    virtual IClock& getClock() = 0;
    virtual GraphicsConfig& getGraphicsConfig() = 0;
    virtual KeyboardConfig& getKeyboardConfig() = 0;

    virtual bool isWindowOpen() = 0;
    virtual bool updateState() = 0;
    virtual void launchWindow() = 0;
    virtual void closeWindow() = 0;
    virtual void runInitialState() = 0;
    virtual void displayRenderedFrame() = 0;
private:

};

class Engine : public IEngine
{
public:
    Engine(){}
    virtual ~Engine(){}
    virtual IClock& getClock();
    virtual GraphicsConfig& getGraphicsConfig();
    virtual KeyboardConfig& getKeyboardConfig();

    virtual bool isWindowOpen();
    virtual bool updateState();
    virtual void closeWindow();
    virtual void displayRenderedFrame();
    virtual void launchWindow();
    virtual void runInitialState();

private:
    Window window;
    Clock clock;
    StateMachine stateMachine;
    GraphicsConfig graphicsConfig;
    KeyboardConfig keyboardConfig;
    sf::Event sfmlEvent;
};

}