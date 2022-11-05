#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Window.h>
#include <Clock.h>
#include <StateMachine.h>
#include <EngineContext.h>
#include <IniParser.h>

namespace Core
{

class IGame
{
public:
    IGame(){}
    virtual ~IGame(){}

    virtual bool isWindowOpen() = 0;

    virtual void setBuildPath(const std::string&) = 0;

    virtual void fetchGraphicsSettings(IIniParser&) = 0;
    virtual void fetchPlayerInputSettings(IIniParser&) = 0;
    virtual void startStateMachine() = 0;
    virtual void openWindow() = 0;

    virtual void update() = 0;
    virtual void updateDeltaTime() = 0;
    virtual void render() = 0;

    virtual std::string getBuildPath() const = 0;
private:
};

class Game : public IGame
{
public:
    Game(IEngineContext&);
    virtual ~Game(){}

    virtual bool isWindowOpen() override {return window.isActive();}

    virtual void setBuildPath(const std::string& path) override {buildPath = path;}

    virtual void fetchGraphicsSettings(IIniParser&) override;
    virtual void fetchPlayerInputSettings(IIniParser&) override;
    virtual void startStateMachine() override;
    virtual void openWindow() override {window.openWithSettings(graphicsConfig);}

    virtual void update() override;
    virtual void updateDeltaTime() override;
    virtual void render() override;

    virtual std::string getBuildPath() const {return buildPath;}
private:
    IWindow& window;
    IClock& clock;
    IStateMachine& stateMachine;
    GraphicsConfig& graphicsConfig;
    KeyboardConfig& keyboardConfig;

    std::string buildPath;

    sf::Event sfmlEvent;
};


}