#pragma once

#include <Window.h>
#include <Clock.h>
#include <StateMachine.h>

namespace Core
{

class IEngineContext
{
public:
    IEngineContext(){}
    virtual ~IEngineContext(){}
    virtual IWindow& getWindow() = 0;
    virtual IClock& getClock() = 0;
    virtual IStateMachine& getStateMachine() = 0;
private:

};

class EngineContext : public IEngineContext
{
public:
    EngineContext(){}
    virtual ~EngineContext(){}
    virtual IWindow& getWindow() override {return window;};
    virtual IClock& getClock() override {return clock;}
    virtual IStateMachine& getStateMachine() override {return stateMachine;}
private:
    Window window;
    Clock clock;
    StateMachine stateMachine;
};

}