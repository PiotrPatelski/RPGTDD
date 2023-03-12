#include <InputListener.hpp>
#include <StateActions.hpp>

namespace Events
{

std::optional<Events::StateAction> MenuInputListener::getActiveAction() const
{
    if (keyboard.isPressedAt("CLOSE"))
    {
        return std::make_optional<StateAction>(ToMainMenuState());
    }
    return std::nullopt;
}

std::optional<Events::StateAction> EditorInputListener::getActiveAction() const
{
    if (keyboard.isPressedAt("PAUSE"))
    {
        return std::make_optional<StateAction>(Pause());
    }
    return std::nullopt;
}

}