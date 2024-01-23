#pragma once
#include <SFML/Graphics.hpp>

namespace Types
{
class Window;
}

namespace Tiles
{

class Tile;

class TilePositionGenerator
{
public:
    TilePositionGenerator(const uint, const uint);
    sf::Vector2i generate();

private:
    const uint tileAmount;
    const uint pixelsPerTile;
    uint counter;
    sf::Vector2i currentPosition;
    void iterateToNextPosition();
};

}