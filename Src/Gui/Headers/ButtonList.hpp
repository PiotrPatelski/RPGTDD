#pragma once
#include <Button.hpp>

namespace Core
{
class IWindow;
}

namespace Gui
{

class ButtonList
{
public:
    ButtonList(const sf::Text& textContent)
    : textContent{textContent},
      active{false}
    {}
    virtual ~ButtonList(){}

    virtual const bool isActive() const {return active;}
    virtual const sf::Text getTextContent() const {return textContent;}
    virtual std::optional<Events::StateAction> getActiveAction() = 0;
    virtual void addSection(const std::string&, Events::StateAction) = 0;
    virtual void update(const sf::Vector2i&) = 0;
    virtual void drawTo(Core::IWindow&) = 0;
protected:
    sf::Text textContent;
    bool active;
};

}