#include <Button.hpp>

namespace Gui
{

sf::Vector2f calculateTextPosOnBackground(const sf::Shape& background, const sf::Text& text)
{
    float textXPosition = background.getPosition().x + (background.getGlobalBounds().width / 2.f) - text.getGlobalBounds().width / 2.f;
	float textYPosition = background.getPosition().y;
    return sf::Vector2f(textXPosition, textYPosition);
}

MainMenuButton::MainMenuButton(
    const sf::Vector2f& position,
    const sf::Vector2f& size,
    const std::string& textContent,
    const sf::Font& font,
    const uint characterSize,
    const EventColor& textColors,
    const EventColor& backgroundColors,
    const EventColor& outlineColors)
: textContent(textContent, font),
  position(position),
  size(size),
  textColors(textColors),
  backgroundColors(backgroundColors),
  outlineColors(outlineColors)
{
    initBackground();
    initText(characterSize);
}

void MainMenuButton::initText(const uint characterSize)
{
    textContent.setCharacterSize(characterSize);
	textContent.setFillColor(textColors.idle);
	textContent.setPosition(calculateTextPosOnBackground(background, textContent));
}

void MainMenuButton::initBackground()
{
    background.setPosition(position);
	background.setSize(size);
	background.setFillColor(backgroundColors.idle);
	background.setOutlineThickness(1.f);
	background.setOutlineColor(outlineColors.idle);
}

}