#pragma once
#include <Tile.hpp>

namespace Tiles
{

class Tile;

class TileBuilder
{
public:
    TileBuilder(){}
    virtual ~TileBuilder(){}
    virtual TileBuilder& atPosition(const sf::Vector2i&) = 0;
    virtual std::unique_ptr<Tile> build() = 0;
};

class DefaultTileBuilder : public TileBuilder
{
public:
    DefaultTileBuilder(const sf::Texture* textureSheet)
    {}
    virtual ~DefaultTileBuilder()
    {}

    virtual DefaultTileBuilder& atPosition(const sf::Vector2i& position);
    virtual std::unique_ptr<Tile> build();
private:
    sf::Vector2i currentPosition;
};

}