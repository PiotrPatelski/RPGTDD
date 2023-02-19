#pragma once

#include <Window.hpp>
#include <Clock.hpp>
#include <StateMachine.hpp>
#include <AssetsManager.hpp>

namespace Core
{

class ICoreBuilder
{
public:
    virtual std::unique_ptr<Types::IWindow> createWindow() const = 0;
    virtual std::unique_ptr<IClock> createClock() const = 0;
    virtual std::unique_ptr<IStateMachine> createStateMachine() const = 0;
};

class CoreBuilder : public ICoreBuilder
{
public:
    virtual std::unique_ptr<Types::IWindow> createWindow() const override
    {return std::make_unique<Types::Window>();}
    virtual std::unique_ptr<IClock> createClock() const override
    {return std::make_unique<Clock>();}
    virtual std::unique_ptr<IStateMachine> createStateMachine() const override
    {return std::make_unique<StateMachine>();}
};

}