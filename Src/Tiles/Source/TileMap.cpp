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
    const uint xIndex = static_cast<uint>(std::floor(position.x / tileBoxSize));
    const uint yIndex = static_cast<uint>(std::floor(position.y / tileBoxSize));
    return map.at(xIndex).at(yIndex) == nullptr;
}

bool TileMap::isValidPosition(const sf::Vector2i& position) const
{
    const bool isXInRange = (position.x <= (map.size() * tileBoxSize));
    const bool isYInRange = (position.y <= (map[0].size() * tileBoxSize));
    const bool isNotNegative = ((position.x >= 0) and (position.y >= 0));
    return isXInRange and isYInRange and isNotNegative;
}

}