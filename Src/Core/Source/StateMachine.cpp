#include <StateMachine.h>

namespace Core
{

StateMachine::StateMachine()
: activeState(nullptr)
{

}

void StateMachine::update(bool isWindowFocused, float deltaTime)
{
    activeState->update(deltaTime);
    if(activeState->isDone())
    {
        activeState->changeState();
    }
}

void StateMachine::runState(std::unique_ptr<States::IState> state)
{
    activeState = std::move(state);
}

}