#pragma once
#include <Button.hpp>

namespace Core
{
class Window;
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

    virtual bool isActive() const {return active;}
    virtual sf::Text getTextContent() const {return textContent;}
    virtual std::optional<Events::StateAction> getActiveAction() = 0;
    virtual VectorMath::ScreenPercentagePoint getPosition() const = 0;
    virtual VectorMath::ScreenPercentagePoint getSize() const = 0;
    virtual void update(const sf::Vector2i&) = 0;
    virtual void drawTo(Types::Window&) = 0;
protected:
    sf::Text textContent;
    bool active;
};

}