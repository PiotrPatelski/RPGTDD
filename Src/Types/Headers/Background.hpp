#pragma once
#include <SFML/Graphics.hpp>
#include <ScreenPercentagePoint.hpp>
#include <Window.hpp>

namespace Types
{

class Background
{
public:
    Background(){}
    Background(
        const VectorMath::ScreenPercentagePoint& position,
        const VectorMath::ScreenPercentagePoint& size)
    : objectPosition(position),
      objectSize(size)
    {
        object.setPosition(objectPosition.toPixels());
        object.setSize(objectSize.toPixels());
        object.setOutlineThickness(1.f);
    }
    virtual ~Background() = default;

    inline VectorMath::ScreenPercentagePoint getPosition() const {return objectPosition;}
    inline VectorMath::ScreenPercentagePoint getSize() const {return objectSize;}
    inline sf::FloatRect getGlobalBounds() const {return object.getGlobalBounds();}
    inline sf::Color getFillColor() const {return object.getFillColor();}

    void setPosition(const VectorMath::ScreenPercentagePoint& newPosition)
    {
        objectPosition = newPosition;
        object.setPosition(newPosition.toPixels());
    }
    void setSize(const VectorMath::ScreenPercentagePoint& newSize)
    {
        objectSize = newSize;
        object.setSize(newSize.toPixels());
    }
    void setFillColor(const sf::Color& color){object.setFillColor(color);}
    void setOutlineColor(const sf::Color& color){object.setOutlineColor(color);}
    void drawTo(Types::IWindow& window){window.draw(object);}
private:
    sf::RectangleShape object;
    VectorMath::ScreenPercentagePoint objectPosition{sf::VideoMode{1, 1}, {0, 0}};
    VectorMath::ScreenPercentagePoint objectSize{sf::VideoMode{1, 1}, {0, 0}};
};

}