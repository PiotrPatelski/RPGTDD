#include <TilePositionGenerator.hpp>
    
namespace Tiles
{

TilePositionGenerator::TilePositionGenerator(const uint tileAmount, const uint pixelsPerTile)
: tileAmount{tileAmount},
  pixelsPerTile(pixelsPerTile),
  counter{0},
  currentPosition{0, 0}
{

}

sf::Vector2i TilePositionGenerator::generate()
{
    const auto generatedPosition = currentPosition;
    iterateToNextPosition();
    return generatedPosition;
}

void TilePositionGenerator::iterateToNextPosition()
{
    if(++counter < tileAmount)
        currentPosition.y += pixelsPerTile;
    else if(counter >= tileAmount)
    {
        currentPosition.x += pixelsPerTile;
        currentPosition.y = 0;
        counter = 0;
    }
}

}