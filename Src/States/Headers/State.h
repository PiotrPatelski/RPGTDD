#pragma once

#include <StateMachine.h>

namespace Core
{
class IStateMachine;
}
namespace States
{

class IState
{
public:
    IState(){}
    virtual ~IState(){}
    
    virtual bool isDone() = 0;
    virtual void markAsDone() = 0;
    virtual void changeState() = 0;
    virtual void update(float) = 0;
};

class State : public IState
{
public:
    State(Core::IStateMachine&);
    virtual ~State(){}

    virtual bool isDone(){return done;}
    virtual void markAsDone(){done = true;}
    virtual void changeState();
    virtual void update(float){}
private:
    bool done{false};
    Core::IStateMachine& stateMachine;
    std::unique_ptr<IState> nextState;
};

class MainMenuState : public State
{
public:
    MainMenuState(Core::IStateMachine&);
    virtual ~MainMenuState() = default;

private:

};

}