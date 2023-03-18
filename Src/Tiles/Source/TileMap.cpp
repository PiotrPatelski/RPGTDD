#include <TileMap.hpp>
#include <Tile.hpp>

namespace Tiles
{

TileMap::TileMap(const uint tileBoxSize, const uint amountOfTilesOnX, const uint amountOfTilesOnY)
: tileBoxSize{tileBoxSize}
{
    map.resize(amountOfTilesOnX);
    for(auto& fieldX : map)
        fieldX.resize(amountOfTilesOnY);
}

bool TileMap::isEmptyAt(const sf::Vector2i& position) const
{
    const uint xIndex = calculateIndex(position.x);
    const uint yIndex = calculateIndex(position.y);
    return map.at(xIndex).at(yIndex) == nullptr;
}

bool TileMap::isValidPosition(const sf::Vector2i& position) const
{
    const bool isXInRange = (position.x <= (map.size() * tileBoxSize));
    const bool isYInRange = (position.y <= (map[0].size() * tileBoxSize));
    const bool isNotNegative = ((position.x >= 0) and (position.y >= 0));
    return isXInRange and isYInRange and isNotNegative;
}

void TileMap::addTile(std::unique_ptr<Tile> tile)
{
    const auto tilePosition = tile->getPosition();
    const uint xIndex = calculateIndex(tilePosition.x);
    const uint yIndex = calculateIndex(tilePosition.y);
    map.at(xIndex).insert(map.at(xIndex).begin() + yIndex, std::move(tile));
}

void TileMap::removeTile(const sf::Vector2i& position)
{
    const uint xIndex = calculateIndex(position.x);
    const uint yIndex = calculateIndex(position.y);
    map.at(xIndex).at(yIndex).reset();
}

uint TileMap::calculateIndex(const uint pixelPos) const
{
    return static_cast<uint>(std::floor(pixelPos / tileBoxSize));
}

}