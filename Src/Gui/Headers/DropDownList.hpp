#pragma once
#include <Button.hpp>

namespace Core
{
class IWindow;
}

namespace Gui
{

class DropDownList
{
public:
    DropDownList(){}
    virtual ~DropDownList(){}

    virtual const bool isActive() const = 0;
    virtual const sf::Text getTextContent() const = 0;
    virtual std::optional<Events::StateAction> getActiveAction() = 0;
    virtual void addSection(const std::string&, Events::StateAction) = 0;
    virtual void update(const sf::Vector2i&) = 0;
    virtual void drawTo(Core::IWindow&) = 0;
};

class MenuDropDownList : public DropDownList
{
public:
    MenuDropDownList(const sf::Text&, std::unique_ptr<IButton>);
    virtual ~MenuDropDownList(){}

    virtual const bool isActive() const override {return active;}
    virtual const sf::Text getTextContent() const {return textContent;}
    virtual std::optional<Events::StateAction> getActiveAction() override;
    virtual void addSection(const std::string&, Events::StateAction) override;
    virtual void update(const sf::Vector2i&) override;
    virtual void drawTo(Core::IWindow&) override;
private:
    Events::StateAction findActiveAction(const sf::Vector2i&);
    sf::Vector2f calculateNextSectionPosition();
    void drawSections(Core::IWindow&);
    bool active;
    sf::Text textContent;
    ActionButton initiatingButton;
    std::vector<ActionButton> sections;
};

}