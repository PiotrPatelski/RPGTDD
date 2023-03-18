#pragma once
#include <ButtonList.hpp>
#include <ButtonBuilder.hpp>
#include <Background.hpp>

namespace Core
{
class Window;
}

namespace Gui
{

class ButtonMenu : public ButtonList
{
public:
    ButtonMenu(
        const sf::Text&,
        const Types::Background&,
        std::vector<ActionButton>&&);
    virtual ~ButtonMenu(){}

    virtual std::optional<Events::StateAction> getActiveAction() override;
    virtual inline VectorMath::ScreenPercentagePoint getPosition() const override {return background.getPosition();}
    virtual inline VectorMath::ScreenPercentagePoint getSize() const override {return background.getSize();}
    virtual void update(const sf::Vector2i&) override;
    virtual void drawTo(Types::Window&) override;
private:
    sf::Vector2f calculateTextPosition();
    uint calculateTextSize(const VectorMath::ScreenPercentagePoint&);
    VectorMath::ScreenPercentagePoint calculateNextSectionPosition();
    VectorMath::ScreenPercentagePoint calculatePositionRelativeToLastButton();
    VectorMath::ScreenPercentagePoint calculatePositionWithNoButtons();
	Types::Background background;
    std::unique_ptr<ButtonBuilder> buttonBuilder;
    std::vector<ActionButton> sections;
};

}