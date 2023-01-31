#include <InputListener.hpp>
#include <StateActions.hpp>

namespace Events
{

std::optional<Events::StateAction> InputListener::getActiveAction() const
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(config.getKeys().at("CLOSE"))))
    {
        return std::make_optional<Events::StateAction>(ToMainMenuState());
    }
    return std::nullopt;
}

}