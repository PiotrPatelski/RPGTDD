#include <ButtonBuilder.hpp>

namespace Gui
{

MainMenuButtonBuilder::MainMenuButtonBuilder(const sf::VideoMode& resolution)
: screenResolution(resolution)
{}

std::unique_ptr<IButton> MainMenuButtonBuilder::build()
{
    std::unique_ptr<IButton> button = std::make_unique<MainMenuButton>(position, size, textContent, font);

    return std::move(button);
}

IButtonBuilder& MainMenuButtonBuilder::withTextContent(const std::string& text)
{
    textContent = text;
    return *this;
}

IButtonBuilder& MainMenuButtonBuilder::atPosition(const float x, const float y)
{
    position = {x, y};
    return *this;
}

IButtonBuilder& MainMenuButtonBuilder::withSize(const float x, const float y)
{
    size = {x, y};
    return *this;
}

IButtonBuilder& MainMenuButtonBuilder::withFont(const sf::Font& font)
{
    this->font = font;
    return *this;
}

}