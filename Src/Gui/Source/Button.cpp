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
    const std::shared_ptr<sf::Font> font,
    const uint characterSize,
    const EventColor& idleColors,
    const EventColor& hoverColors,
    const EventColor& activeColors,
    std::unique_ptr<Events::IButtonEventHandler> eventHandler)
: font(font),
  textContent(textContent, *font),
  position(position),
  size(size),
  idleColors(idleColors),
  hoverColors(hoverColors),
  activeColors(activeColors),
  eventHandler(std::move(eventHandler))
{
    initBackground();
    initText(characterSize);
}

void MainMenuButton::initText(const uint characterSize)
{
    textContent.setCharacterSize(characterSize);
	textContent.setFillColor(idleColors.text);
	textContent.setPosition(calculateTextPosOnBackground(background, textContent));
}

void MainMenuButton::initBackground()
{
    background.setPosition(position);
	background.setSize(size);
	background.setFillColor(idleColors.background);
	background.setOutlineThickness(1.f);
	background.setOutlineColor(idleColors.outline);
}

void MainMenuButton::setColor(const EventColor& colors)
{
    background.setFillColor(colors.background);
    background.setOutlineColor(colors.outline);
    textContent.setFillColor(colors.text);
}

void MainMenuButton::update(const sf::Vector2i& mousePosOnWindow)
{
    active = false;
    if(background.getGlobalBounds().contains(
        static_cast<sf::Vector2f>(mousePosOnWindow)))
    {
        setColor(hoverColors);
        if(eventHandler->isPressed())
        {
            setColor(activeColors);
            active = true;
        }
    }
    else
        setColor(idleColors);
}

}