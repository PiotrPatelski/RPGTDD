#pragma once

#include <SFML/Window.hpp>
#include <StateActions.hpp>
#include <ButtonList.hpp>

namespace Core
{
class Window;
}

namespace Events
{
class GuiAction;
}

namespace Gui
{

class UserInterface
{
public:
    UserInterface(){}
    virtual ~UserInterface(){}

    virtual void acceptRequest(Events::GuiAction&) = 0;

    virtual void addButton(std::unique_ptr<Button>, Events::StateAction) = 0;
    virtual void addButtonList(std::unique_ptr<ButtonList>) = 0;
    virtual std::optional<Events::StateAction> getActiveAction() = 0;
    virtual void drawTo(Types::Window&) = 0;
    virtual void update(const sf::Vector2i&) = 0;
};

}