#include <StateMachine.hpp>

namespace Core
{

StateMachine::StateMachine()
: activeState(nullptr)
{

}

void StateMachine::update(const Types::IWindow& window, const float deltaTime)
{
    activeState->update(window, deltaTime);
    if(activeState->isReadyToChange())
    {
        setState(activeState->getNextState());
    }
}

void StateMachine::setState(std::shared_ptr<States::IState> state)
{
    activeState.swap(state);
}

}