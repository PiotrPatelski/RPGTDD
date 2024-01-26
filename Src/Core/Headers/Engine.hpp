#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <CoreBuilder.hpp>
#include <Config.hpp>

namespace Core
{

class IEngine
{
public:
    IEngine(){}
    virtual ~IEngine(){}
    virtual void updateDeltaTime() = 0;
    virtual bool isWindowOpen() = 0;
    virtual bool updateState() = 0;
    virtual void launchWindow(const FileMgmt::GraphicsConfig&) = 0;
    virtual void closeWindow() = 0;
    virtual void runInitialState(std::shared_ptr<FileMgmt::IConfigManager>) = 0;
    virtual void displayRenderedFrame() = 0;
private:

};

class Engine : public IEngine
{
public:
    Engine(const CoreBuilder&);
    virtual ~Engine(){}
    virtual void updateDeltaTime();
    virtual bool isWindowOpen();
    virtual bool updateState();
    virtual void launchWindow(const FileMgmt::GraphicsConfig&);
    virtual void closeWindow();
    virtual void runInitialState(std::shared_ptr<FileMgmt::IConfigManager>);
    virtual void displayRenderedFrame();
private:
    std::unique_ptr<Types::Window> window;
    std::unique_ptr<Clock> clock;
    std::unique_ptr<StateMachine> stateMachine;
    sf::Event sfmlEvent;
};

}