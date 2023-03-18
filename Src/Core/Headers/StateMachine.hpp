#pragma once

#include <MainMenuState.hpp>

namespace Core
{

class StateMachine
{
public:
    StateMachine();
    virtual ~StateMachine(){}

    virtual bool isAnyStateActive() {return activeState != nullptr;}
    virtual std::shared_ptr<States::IState> getCurrentState() {return activeState;}
    virtual void setState(std::shared_ptr<States::IState>);
    virtual void update(const Types::Window&, const float);
private:
    std::shared_ptr<States::IState> activeState;
};

}