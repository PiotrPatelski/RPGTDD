#include <ButtonBuilder.hpp>

#include <PixelsPoint.hpp>

namespace Gui
{

EventColor DEFAULT_IDLE_COLORS = EventColor{
    sf::Color(70, 70, 70, 200),
    sf::Color(70, 70, 70, 50),
    sf::Color::Transparent};

EventColor DEFAULT_HOVER_COLORS = EventColor{
    sf::Color(250, 250, 150, 250),
    sf::Color(250, 250, 150, 50),
    sf::Color::Transparent};

EventColor DEFAULT_ACTIVE_COLORS = EventColor{
    sf::Color(20, 20, 20, 50),
    sf::Color(20, 20, 20, 50),
    sf::Color::Transparent};

MenuButtonBuilder::MenuButtonBuilder()
: idleColors(DEFAULT_IDLE_COLORS),
  hoverColors(DEFAULT_HOVER_COLORS),
  activeColors(DEFAULT_ACTIVE_COLORS)
{}

std::unique_ptr<Button> MenuButtonBuilder::build()
{
    return std::make_unique<MainMenuButton>(
        position,
        size,
        textContent,
        idleColors,
        hoverColors,
        activeColors,
        std::make_unique<Events::ButtonEventHandler>());
}

MenuButtonBuilder& MenuButtonBuilder::withTextContent(const sf::Text& text)
{
    textContent = std::make_optional<sf::Text>(text);
    return *this;
}

MenuButtonBuilder& MenuButtonBuilder::atPosition(const VectorMath::ScreenPercentagePoint& position)
{
    this->position = position;
    return *this;
}

MenuButtonBuilder& MenuButtonBuilder::withSize(const VectorMath::ScreenPercentagePoint& size)
{
    this->size = size;
    return *this;
}

}