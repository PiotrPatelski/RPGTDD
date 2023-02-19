#pragma once
#include <SFML/Graphics.hpp>

namespace Types
{
class Background;
}

namespace Gui
{
class Button;
}

namespace VectorMath
{

class ScreenPercentagePoint;

class PauseMenuCalculator
{
public:
    PauseMenuCalculator(const sf::VideoMode& resolution)
    : resolution(resolution)
    {}
    uint calculateTextSize(const sf::Vector2f&) const;
    sf::Vector2f calculateTextPosition(const Types::Background&, const sf::FloatRect&) const;
    ScreenPercentagePoint calculatePositionWithNoButtons(const Types::Background&) const;
    ScreenPercentagePoint calculatePositionRelativeToButtons(
        const ScreenPercentagePoint&,
        const ScreenPercentagePoint&,
        const ScreenPercentagePoint&,
        const Types::Background&) const;
private:
    sf::VideoMode resolution;
};

}