#include <StateMachine.hpp>

namespace Core
{

StateMachine::StateMachine()
: activeState(nullptr)
{

}

void StateMachine::update(const sf::Vector2i& mousePosOnWindow, const float deltaTime)
{
    activeState->update(mousePosOnWindow, deltaTime);
    if(activeState->isDone())
    {
        setState(activeState->getNextState());
    }
}

void StateMachine::setState(std::shared_ptr<States::IState> state)
{
    activeState.swap(state);
}

}