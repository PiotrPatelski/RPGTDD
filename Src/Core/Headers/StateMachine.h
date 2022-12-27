#pragma once

#include <MainMenuState.h>

namespace Core
{

class IStateMachine
{
public:
    IStateMachine(){}
    virtual ~IStateMachine(){}

    virtual bool isNoStateActive() = 0;
    virtual std::shared_ptr<States::IState> getCurrentState() = 0;
    virtual void runState(std::shared_ptr<States::IState>) = 0;
    virtual void update(bool, float) = 0;
};

class StateMachine : public IStateMachine
{
public:
    StateMachine();
    virtual ~StateMachine(){}

    virtual bool isNoStateActive() override {return activeState == nullptr;}
    virtual std::shared_ptr<States::IState> getCurrentState() override {return activeState;}
    virtual void runState(std::shared_ptr<States::IState>) override;
    virtual void update(bool, float) override;
private:
    std::shared_ptr<States::IState> activeState;
};

}