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
    virtual TileBuilder& atPosition(const sf::Vector2i) {return *this;}
    virtual std::unique_ptr<Tile> build() {return std::make_unique<Tile>();}
};

}