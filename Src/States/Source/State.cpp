#include <State.h>

namespace States
{

State::State(Core::IStateMachine& stateMachine)
: stateMachine{stateMachine}
{

}

void State::changeState()
{
    stateMachine.runState(std::move(nextState));
}

MainMenuState::MainMenuState(Core::IStateMachine& stateMachine)
: State::State(stateMachine)
{

}

}