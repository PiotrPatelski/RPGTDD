#pragma once

#include <State.h>

namespace Core
{

class IStateMachine
{
public:
    IStateMachine(){}
    virtual ~IStateMachine(){}

    virtual bool isNoStateActive() = 0;
    virtual States::StateOutput getOutput() = 0;
    virtual void runState(std::unique_ptr<States::IState>) = 0;
    virtual void update(bool, float) = 0;
};

class StateMachine : public IStateMachine
{
public:
    StateMachine();
    virtual ~StateMachine(){}

    virtual bool isNoStateActive() override {return activeState == nullptr;}
    virtual States::StateOutput getOutput() override {return activeState->generateOutput();}
    virtual void runState(std::unique_ptr<States::IState>) override;
    virtual void update(bool, float) override;
private:
    std::unique_ptr<States::IState> activeState;
};

}