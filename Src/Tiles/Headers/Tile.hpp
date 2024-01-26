#pragma once
#include <SFML/Graphics.hpp>

namespace Types
{
class Window;
}

namespace Tiles
{

class Tile
{
public:
    Tile() = default;
    virtual ~Tile() = default;
    virtual sf::Vector2i getPosition() const = 0;
    virtual void setPosition(const sf::Vector2i&) = 0;
    virtual void drawTo(Types::Window&) = 0;
};

class NormalTile : public Tile
{
public:
    NormalTile(const sf::Texture* texture)
    {
        sprite.setTexture(*texture);
    }
    virtual ~NormalTile() = default;
    virtual sf::Vector2i getPosition() const;
    virtual void setPosition(const sf::Vector2i&);
    virtual void drawTo(Types::Window&);
private:
    sf::Sprite sprite;
};

}