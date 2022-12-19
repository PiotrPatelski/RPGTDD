#include <ButtonBuilder.hpp>

namespace Gui
{

EventColor DEFAULT_TEXT_COLORS = EventColor{
    sf::Color(70, 70, 70, 200),
    sf::Color(250, 250, 150, 250),
    sf::Color(20, 20, 20, 50)};

EventColor DEFAULT_BACKGROUND_COLORS = EventColor{
    sf::Color(70, 70, 70, 0),
    sf::Color(250, 250, 150, 0),
    sf::Color(20, 20, 20, 0)};

EventColor TRANSPARENT_EVENT_COLORS = EventColor{
    sf::Color::Transparent,
    sf::Color::Transparent,
    sf::Color::Transparent};

uint calculateFontSize(const sf::VideoMode& screenResolution)
{
    const uint divider = 60;
    return static_cast<unsigned>((screenResolution.width + screenResolution.height) / divider);
}

MainMenuButtonBuilder::MainMenuButtonBuilder(const sf::VideoMode& resolution)
: screenResolution(resolution),
  textColors(DEFAULT_TEXT_COLORS),
  backgroundColors(DEFAULT_BACKGROUND_COLORS),
  outlineColors(TRANSPARENT_EVENT_COLORS)
{}

std::unique_ptr<IButton> MainMenuButtonBuilder::build()
{
    std::unique_ptr<IButton> button = std::make_unique<MainMenuButton>(
        position,
        size,
        textContent,
        font,
        calculateFontSize(screenResolution),
        textColors,
        backgroundColors,
        outlineColors);

    return std::move(button);
}

IButtonBuilder& MainMenuButtonBuilder::withTextContent(const std::string& text)
{
    textContent = text;
    return *this;
}

IButtonBuilder& MainMenuButtonBuilder::atPosition(const float x, const float y)
{
    const float xPixels = ScreenPercentage(screenResolution).toPixelsOnX(x);
    const float yPixels = ScreenPercentage(screenResolution).toPixelsOnY(y);
    position = sf::Vector2f(xPixels, yPixels);
    return *this;
}

IButtonBuilder& MainMenuButtonBuilder::withSize(const float width, const float height)
{
    const float widthPixels = ScreenPercentage(screenResolution).toPixelsOnX(width);
    const float heightPixels = ScreenPercentage(screenResolution).toPixelsOnY(height);
    size = sf::Vector2f(widthPixels, heightPixels);
    return *this;
}

IButtonBuilder& MainMenuButtonBuilder::withFont(const sf::Font& font)
{
    this->font = font;
    return *this;
}

}