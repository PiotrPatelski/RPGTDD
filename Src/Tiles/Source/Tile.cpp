#include <Tile.hpp>
#include <Window.hpp>

namespace Tiles
{

void Tile::setPosition(const sf::Vector2i& position)
{
    sprite.setPosition(static_cast<sf::Vector2f>(position));
}

void Tile::drawTo(Types::Window& window)
{
    window.draw(sprite);
}

sf::Vector2i Tile::getPosition() const
{
    return static_cast<sf::Vector2i>(sprite.getPosition());
}

}