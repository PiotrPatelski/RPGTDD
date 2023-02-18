#pragma once

#include <StateActions.hpp>
#include <ButtonList.hpp>
#include <UserInterface.hpp>

namespace Core
{
class IWindow;
}

namespace Events
{
class GuiAction;
}

namespace Gui
{

class MenuGui : public UserInterface
{
public:
    MenuGui(){}
    virtual ~MenuGui(){}
    virtual void acceptRequest(Events::GuiAction&) override;
    virtual void addButton(std::unique_ptr<Button>, Events::StateAction) override;
    virtual void addButtonList(std::unique_ptr<ButtonList>) override;
    virtual std::optional<Events::StateAction> getActiveAction() override;
    virtual void drawTo(Core::IWindow&) override;
    virtual void update(const sf::Vector2i&) override;
private:
    std::optional<Events::StateAction> pollActionFromButtons();
    std::optional<Events::StateAction> pollActionFromButtonLists();
    std::vector<ActionButton> buttons;
    std::vector<std::unique_ptr<ButtonList>> dropDownLists;
};

}