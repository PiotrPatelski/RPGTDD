#pragma once

#include <Engine.h>
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
    virtual void updateClock() = 0;
    virtual void render() = 0;

    virtual std::string getBuildPath() const = 0;
private:
};

class Game : public IGame
{
public:
    Game(std::unique_ptr<IEngine> engine);
    virtual ~Game(){}

    virtual bool isWindowOpen() override {return engine->isWindowOpen();}

    virtual void setBuildPath(const std::string& path) override {buildPath = path;}

    virtual void fetchGraphicsSettings(IIniParser&) override;
    virtual void fetchPlayerInputSettings(IIniParser&) override;
    virtual void startStateMachine() override;
    virtual void openWindow() override;
    virtual void update() override;
    virtual void updateClock() override;
    virtual void render() override;

    virtual std::string getBuildPath() const {return buildPath;}
private:
    std::unique_ptr<IEngine> engine;

    std::string buildPath;
};


}