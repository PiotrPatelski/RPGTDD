#include <Tile.hpp>
#include <Window.hpp>

namespace Tiles
{

void NormalTile::setPosition(const sf::Vector2i& position)
{
    sprite.setPosition(static_cast<sf::Vector2f>(position));
}

void NormalTile::drawTo(Types::Window& window)
{
    window.draw(sprite);
}

sf::Vector2i NormalTile::getPosition() const
{
    return static_cast<sf::Vector2i>(sprite.getPosition());
}

}