#pragma once
#include <ButtonList.hpp>

namespace Core
{
class IWindow;
}

namespace Gui
{

class DropDownList : public ButtonList
{
public:
    DropDownList(const sf::Text&, std::unique_ptr<IButton>);
    virtual ~DropDownList(){}

    virtual std::optional<Events::StateAction> getActiveAction() override;
    virtual void addSection(const std::string&, Events::StateAction) override;
    virtual void update(const sf::Vector2i&) override;
    virtual void drawTo(Core::IWindow&) override;
private:
    void setTextPosition();
    Events::StateAction findActiveAction(const sf::Vector2i&);
    sf::Vector2f calculateNextSectionPosition();
    void drawSections(Core::IWindow&);
    ActionButton initiatingButton;
    std::vector<ActionButton> sections;
};

}