#pragma once
#include <Tile.hpp>

namespace Tiles
{

class Tile;

class TileBuilder
{
public:
    TileBuilder() = default;
    virtual ~TileBuilder() = default;

    virtual TileBuilder& atPosition(const sf::Vector2i& position);
    virtual std::unique_ptr<Tile> build();
private:
    sf::Vector2i currentPosition;
};

}