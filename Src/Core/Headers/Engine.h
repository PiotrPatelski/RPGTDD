#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <CoreBuilder.h>
#include <Config.h>

namespace Core
{

class IEngine
{
public:
    IEngine(){}
    virtual ~IEngine(){}
    virtual void updateDeltaTime() = 0;
    virtual Config& getConfig() = 0;

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
    Engine(const ICoreBuilder&);
    virtual ~Engine(){}
    virtual void updateDeltaTime();
    virtual Config& getConfig();

    virtual bool isWindowOpen();
    virtual bool updateState();
    virtual void closeWindow();
    virtual void displayRenderedFrame();
    virtual void launchWindow();
    virtual void runInitialState();

private:
    std::unique_ptr<IWindow> window;
    std::unique_ptr<IClock> clock;
    std::unique_ptr<IStateMachine> stateMachine;
    Config config;
    sf::Event sfmlEvent;
};

}