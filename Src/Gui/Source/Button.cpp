#include <Button.hpp>

namespace Gui
{

MainMenuButton::MainMenuButton(
    const sf::Vector2f& position,
    const sf::Vector2f& size,
    const std::string& textContent,
    const sf::Font& font)
: textContent(textContent, font),
  position(position),
  size(size)
{

}

}