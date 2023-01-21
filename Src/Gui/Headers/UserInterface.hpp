#pragma once

#include <SFML/Window.hpp>
#include <ButtonActions.hpp>
#include <Button.hpp>

namespace Core
{
class IWindow;
}

namespace Gui
{

struct ActionButton
{
    std::shared_ptr<Gui::IButton> object;
    Events::StateAction action;
};

class UserInterface
{
public:
    UserInterface(){}
    virtual ~UserInterface(){}

    virtual void addButton(std::shared_ptr<IButton> button, Events::StateAction action);
    virtual std::optional<Events::StateAction> getActiveAction();
    virtual void drawTo(Core::IWindow&);
    virtual void update(const Core::IWindow&);
private:
    std::vector<ActionButton> buttons;
};

}