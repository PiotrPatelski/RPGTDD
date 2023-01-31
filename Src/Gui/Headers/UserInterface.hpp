#pragma once

#include <SFML/Window.hpp>
#include <StateActions.hpp>
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

class IUserInterface
{
public:
    IUserInterface(){}
    virtual ~IUserInterface(){}

    virtual void addButton(std::shared_ptr<IButton>, Events::StateAction) = 0;
    virtual std::optional<Events::StateAction> getActiveAction() = 0;
    virtual void drawTo(Core::IWindow&) = 0;
    virtual void update(const Core::IWindow&) = 0;
};

class UserInterface : public IUserInterface
{
public:
    UserInterface(){}
    virtual ~UserInterface(){}

    virtual void addButton(std::shared_ptr<IButton>, Events::StateAction) override;
    virtual std::optional<Events::StateAction> getActiveAction() override;
    virtual void drawTo(Core::IWindow&) override;
    virtual void update(const Core::IWindow&) override;
private:
    std::vector<ActionButton> buttons;
};

}