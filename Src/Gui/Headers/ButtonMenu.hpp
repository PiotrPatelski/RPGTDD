#pragma once
#include <ButtonList.hpp>
#include <ButtonBuilder.hpp>

namespace Core
{
class IWindow;
}

namespace Gui
{

class ButtonMenu : public ButtonList
{
public:
    ButtonMenu(
        const std::string&,
        const sf::Font&,
        const sf::VideoMode&,
        const sf::Vector2f&,
        const sf::Vector2f&,
        std::unique_ptr<ButtonBuilder>);
    virtual ~ButtonMenu(){}

    virtual std::optional<Events::StateAction> getActiveAction() override;
    virtual void addSection(const std::optional<sf::Text>, Events::StateAction) override;
    virtual void update(const sf::Vector2i&) override;
    virtual void drawTo(Core::IWindow&) override;
private:
    sf::Vector2f calculateTextPosition(const sf::VideoMode&);
    sf::Vector2f calculateNextSectionPosition();
    sf::Vector2f calculatePositionRelativeToLastButton();
    sf::Vector2f calculatePositionWithNoButtons();
    sf::RectangleShape background;
	sf::RectangleShape container;
    std::unique_ptr<ButtonBuilder> buttonBuilder;
    std::vector<ActionButton> sections;
};

}