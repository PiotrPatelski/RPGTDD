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
    Tile()
    {
        //TODO remove placeholder code
        sf::Texture texture; //TMP
        texture.create(64, 64); //TMP
        sprite.setTexture(texture); //TMP
        sprite.setColor(sf::Color(0, 255, 0)); //TMP
    }
    virtual ~Tile() = default;
    virtual sf::Vector2i getPosition() const;
    virtual void setPosition(const sf::Vector2i&);
    virtual void drawTo(Types::Window&);
private:
    sf::Sprite sprite;
};

}