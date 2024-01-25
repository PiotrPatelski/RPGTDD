#include <TileMap.hpp>
#include <Tile.hpp>
#include <TilePositionGenerator.hpp>

namespace Tiles
{

void applyEmptyFields(std::vector<TileField>& column, const uint amount, TilePositionGenerator& positioner)
{
    column.reserve(amount);
    for(uint row = 0; row < amount; row++)
        column.push_back(TileField(positioner.generate()));
}

TileMap::TileMap(const uint tileBoxSize, const uint amountOfTilesOnX, const uint amountOfTilesOnY)
: tileBoxSize{tileBoxSize}
{
    TilePositionGenerator positioner{amountOfTilesOnY, tileBoxSize};

    map.resize(amountOfTilesOnX);
    for(auto& fieldX : map)
        applyEmptyFields(fieldX, amountOfTilesOnY, positioner);
}

bool TileMap::isEmptyAt(const sf::Vector2i& position) const
{
    const uint xIndex = calculateIndex(position.x);

    const uint yIndex = calculateIndex(position.y);//Later to add validator class for checks

    return map.at(xIndex).at(yIndex).isEmpty();
}

bool TileMap::isValidPosition(const sf::Vector2i& position) const
{
    const bool isXInRange = (position.x <= (map.size() * tileBoxSize));

    const bool isYInRange = (position.y <= (map[0].size() * tileBoxSize));

    const bool isNotNegative = ((position.x >= 0) and (position.y >= 0));//Later to add validator class for checks

    return isXInRange and isYInRange and isNotNegative;
}

void TileMap::addTile(std::unique_ptr<Tile> tile)
{
    const auto position = tile->getPosition();
    const uint xIndex = calculateIndex(position.x);
    const uint yIndex = calculateIndex(position.y);//Later to add validator class for checks

    auto& targetMapField = map.at(xIndex).at(yIndex);
    if(not targetMapField.isFull());
        targetMapField.pushTile(std::move(tile));
}

void TileMap::removeTile(const sf::Vector2i& position)
{
    const uint xIndex = calculateIndex(position.x);
    const uint yIndex = calculateIndex(position.y);//Later to add validator class for checks
    map.at(xIndex).at(yIndex).popTile();
}

uint TileMap::calculateIndex(const uint pixelPos) const
{
    return static_cast<uint>(std::floor(pixelPos / tileBoxSize));
}

void TileMap::update()
{

}

void TileMap::drawTo(Types::Window& window)
{
    for(auto& fieldX : map)
    {
        for(auto& fieldY : fieldX)
            fieldY.drawTo(window);
    }
}

}