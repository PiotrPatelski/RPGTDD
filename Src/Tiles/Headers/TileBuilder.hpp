#pragma once
#include <SFML/Graphics.hpp>
#include <Tile.hpp>

namespace Tiles
{

class TileBuilder
{
public:
    TileBuilder() = default;
    virtual ~TileBuilder() = default;
    virtual std::unique_ptr<Tile> build() {return std::make_unique<Tile>();}
};

}