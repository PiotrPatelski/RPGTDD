#pragma once

#include <Window.hpp>
#include <Clock.hpp>
#include <StateMachine.hpp>
#include <AssetsManager.hpp>

namespace Core
{

class CoreBuilder
{
public:
    virtual std::unique_ptr<Types::Window> createWindow() const {return std::make_unique<Types::Window>();}
    virtual std::unique_ptr<Clock> createClock() const {return std::make_unique<Clock>();}
    virtual std::unique_ptr<StateMachine> createStateMachine() const {return std::make_unique<StateMachine>();}
};

}