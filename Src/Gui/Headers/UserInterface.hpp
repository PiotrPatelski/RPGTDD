#pragma once

#include <SFML/Window.hpp>
#include <StateActions.hpp>
#include <DropDownList.hpp>

namespace Core
{
class IWindow;
}

namespace Gui
{

class UserInterface
{
public:
    UserInterface(){}
    virtual ~UserInterface(){}

    virtual void addButton(std::unique_ptr<IButton>, Events::StateAction) = 0;
    virtual void addDropDownList(std::unique_ptr<DropDownList>) = 0;
    virtual std::optional<Events::StateAction> getActiveAction() = 0;
    virtual void drawTo(Core::IWindow&) = 0;
    virtual void update(const sf::Vector2i&) = 0;
};

class MenuGui : public UserInterface
{
public:
    MenuGui(){}
    virtual ~MenuGui(){}

    virtual void addButton(std::unique_ptr<IButton>, Events::StateAction) override;
    virtual void addDropDownList(std::unique_ptr<DropDownList>) override;
    virtual std::optional<Events::StateAction> getActiveAction() override;
    virtual void drawTo(Core::IWindow&) override;
    virtual void update(const sf::Vector2i&) override;
private:
    std::optional<Events::StateAction> pollActionFromButtons();
    std::optional<Events::StateAction> pollActionFromDropDownLists();
    std::vector<ActionButton> buttons;
    std::vector<std::unique_ptr<DropDownList>> dropDownLists;
};

}