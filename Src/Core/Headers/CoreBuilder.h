#pragma once

#include <Window.h>
#include <Clock.h>
#include <StateMachine.h>

namespace Core
{

class ICoreBuilder
{
public:
    virtual std::unique_ptr<IWindow> createWindow() const = 0;
    virtual std::unique_ptr<IClock> createClock() const = 0;
    virtual std::unique_ptr<IStateMachine> createStateMachine() const = 0;
};

class CoreBuilder : public ICoreBuilder
{
public:
    virtual std::unique_ptr<IWindow> createWindow() const override 
    {return std::move(std::make_unique<Window>());}
    virtual std::unique_ptr<IClock> createClock() const override
    {return std::move(std::make_unique<Clock>());}
    virtual std::unique_ptr<IStateMachine> createStateMachine() const override
    {return std::move(std::make_unique<StateMachine>());}
};

}