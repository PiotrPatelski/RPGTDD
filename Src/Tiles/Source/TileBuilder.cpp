#include <TileBuilder.hpp>
#include <Tile.hpp>

namespace Tiles
{

std::unique_ptr<Tile> DefaultTileBuilder::build()
{
    auto tile = std::make_unique<Tile>();
    tile->setPosition(currentPosition);
    return std::move(tile);
}

DefaultTileBuilder& DefaultTileBuilder::atPosition(const sf::Vector2i& position)
{
    currentPosition = position;
    return *this;
}

}