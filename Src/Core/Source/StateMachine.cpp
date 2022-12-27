#include <StateMachine.h>

namespace Core
{

StateMachine::StateMachine()
: activeState(nullptr)
{

}

void StateMachine::update(bool isWindowFocused, float deltaTime)
{
    if(isWindowFocused)
    {
        activeState->update(deltaTime);
        if(activeState->isDone())
        {
            runState(activeState->getNextState());
        }
    }
}

void StateMachine::runState(std::shared_ptr<States::IState> state)
{
    activeState.swap(state);
}

}