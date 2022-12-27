#pragma once

#include <Engine.h>
#include <IniParser.hpp>

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
    virtual void updateClock() = 0;
    virtual void render() = 0;
private:
};

class Game : public IGame
{
public:
    Game(std::unique_ptr<IEngine> engine);
    virtual ~Game(){}

    virtual bool isWindowOpen() override {return engine->isWindowOpen();}
    virtual void startStateMachine() override;
    virtual void openWindow() override;

    virtual void update() override;
    virtual void updateClock() override;
    virtual void render() override;
private:
    std::shared_ptr<ConfigManager> config;
    std::unique_ptr<IEngine> engine;
};


}