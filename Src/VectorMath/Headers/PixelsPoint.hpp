#pragma once

#include <SFML/Window.hpp>

namespace VectorMath
{
class ScreenPercentagePoint;

class PixelsPoint
{
public:
    PixelsPoint(const sf::VideoMode&, const sf::Vector2f&);
    PixelsPoint(const ScreenPercentagePoint&);
    PixelsPoint(const PixelsPoint&);
    PixelsPoint(PixelsPoint&&);
    ~PixelsPoint(){}
    PixelsPoint& operator=(const PixelsPoint&);
    PixelsPoint& operator=(PixelsPoint&&);

    sf::VideoMode getResolution() const;
    sf::Vector2f toScreenPercentage() const;
    sf::Vector2f value() const;
private:
    float toScreenPercentageOnX(const float) const;
    float toScreenPercentageOnY(const float) const;
    sf::VideoMode resolution;
    sf::Vector2f val;
};

}