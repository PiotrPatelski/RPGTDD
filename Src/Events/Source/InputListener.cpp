#include <InputListener.hpp>
#include <StateActions.hpp>

namespace Events
{

std::optional<Events::StateAction> MenuInputListener::getActiveAction() const
{
    if (keyboard.isPressedAt("CLOSE"))
    {
        return std::make_optional<Events::StateAction>(ToMainMenuState());
    }
    return std::nullopt;
}

}