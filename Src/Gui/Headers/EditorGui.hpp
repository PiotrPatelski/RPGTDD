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

class EditorGui : public UserInterface
{
public:
    EditorGui()
    : paused{false}
    {}
    virtual ~EditorGui(){}
    virtual void acceptRequest(Events::GuiAction&) override;
    virtual void addButton(std::unique_ptr<IButton>, Events::StateAction) override;
    virtual void addButtonList(std::unique_ptr<ButtonList>) override;
    virtual std::optional<Events::StateAction> getActiveAction() override;
    virtual void drawTo(Core::IWindow&) override;
    virtual void update(const sf::Vector2i&) override;
    virtual void addPauseMenu(std::unique_ptr<ButtonList>);
    virtual void togglePause() {paused = not(paused);}
    virtual bool isPaused() const {return paused;}
private:
    std::optional<Events::StateAction> pollActionFromButtons();
    std::optional<Events::StateAction> pollActionFromButtonLists();
    std::vector<ActionButton> buttons;
    std::vector<std::unique_ptr<ButtonList>> dropDownLists;
    std::unique_ptr<ButtonList> pauseMenu;
    bool paused;
};

}