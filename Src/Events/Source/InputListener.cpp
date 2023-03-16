#include <InputListener.hpp>
#include <StateActions.hpp>

namespace Events
{

std::optional<Events::StateAction> MenuInputListener::getKeyboardAction() const
{
    if (keyboard.isPressedAt("CLOSE"))
        return std::make_optional<StateAction>(ToMainMenuState());
    return std::nullopt;
}

std::optional<Events::StateAction> EditorInputListener::getKeyboardAction() const
{
    if (keyboard.isPressedAt("PAUSE"))
        return std::make_optional<StateAction>(Pause());
    return std::nullopt;
}

std::optional<Events::StateAction> EditorInputListener::getMouseAction(const sf::Vector2i& mousePosition) const
{
    if(mouse->isLeftPressed())
        return std::make_optional<StateAction>(AddTile(mousePosition));
    else if(mouse->isRightPressed())
        return std::make_optional<StateAction>(RemoveTile(mousePosition));
    return std::nullopt;
}

}