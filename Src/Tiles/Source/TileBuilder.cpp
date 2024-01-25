#include <TileBuilder.hpp>
#include <Tile.hpp>

namespace Tiles
{

std::unique_ptr<Tile> TileBuilder::build()
{
    auto tile = std::make_unique<Tile>();
    tile->setPosition(currentPosition);
    return std::move(tile);
}

TileBuilder& TileBuilder::atPosition(const sf::Vector2i& position)
{
    currentPosition = position;
    return *this;
}

}