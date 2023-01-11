#include <ButtonBuilder.hpp>

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

uint calculateFontSize(const sf::VideoMode& screenResolution)
{
    const uint divider = 70;
    return static_cast<unsigned>((screenResolution.width + screenResolution.height) / divider);
}

ButtonBuilder::ButtonBuilder(const sf::VideoMode& resolution)
: screenResolution(resolution),
  idleColors(DEFAULT_IDLE_COLORS),
  hoverColors(DEFAULT_HOVER_COLORS),
  activeColors(DEFAULT_ACTIVE_COLORS)
{}

std::unique_ptr<IButton> ButtonBuilder::build()
{
    std::unique_ptr<IButton> button = std::make_unique<MainMenuButton>(
        position,
        size,
        textContent,
        font,
        calculateFontSize(screenResolution),
        idleColors,
        hoverColors,
        activeColors,
        std::make_unique<Events::ButtonEventHandler>());
        // action);

    return button;
}

ButtonBuilder& ButtonBuilder::withTextContent(const std::string& text)
{
    textContent = text;
    return *this;
}

ButtonBuilder& ButtonBuilder::atPosition(const float x, const float y)
{
    const float xPixels = ScreenPercentage(screenResolution).toPixelsOnX(x);
    const float yPixels = ScreenPercentage(screenResolution).toPixelsOnY(y);
    position = sf::Vector2f(xPixels, yPixels);
    return *this;
}

ButtonBuilder& ButtonBuilder::withSize(const float width, const float height)
{
    const float widthPixels = ScreenPercentage(screenResolution).toPixelsOnX(width);
    const float heightPixels = ScreenPercentage(screenResolution).toPixelsOnY(height);
    size = sf::Vector2f(widthPixels, heightPixels);
    return *this;
}

ButtonBuilder& ButtonBuilder::withFont(const sf::Font& font)
{
    this->font = font;
    return *this;
}

}