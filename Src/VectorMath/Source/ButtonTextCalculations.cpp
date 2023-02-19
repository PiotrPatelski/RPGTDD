#include <ButtonTextCalculations.hpp>
#include <Background.hpp>

namespace VectorMath
{

sf::Vector2f calculateTextPosOnBackground(const Types::Background& background, const sf::FloatRect& textRect)
{
    float textXPosition = background.getPosition().toPixels().x + (background.getGlobalBounds().width / 2.f) - textRect.width / 2.f;
	float textYPosition = background.getPosition().toPixels().y;
    return sf::Vector2f(textXPosition, textYPosition);
}

uint calculateFontSize(const sf::Vector2f& buttonSize)
{
    const auto x = buttonSize.x <= 0 ? 0 : buttonSize.x;
    const auto y = buttonSize.y <= 0 ? 0 : buttonSize.y;
    const uint divider = static_cast<unsigned>(x + y);
    if(divider > 0)
        return (divider / 8);
    return 0;
}

}