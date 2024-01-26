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
    DefaultTileBuilder(const sf::Texture*, const std::vector<std::string>&);
    virtual ~DefaultTileBuilder()
    {}

    virtual DefaultTileBuilder& atPosition(const sf::Vector2i&);
    virtual std::unique_ptr<Tile> build();
private:
    sf::Vector2i currentPosition;
    const sf::Texture* tileTextureSheet;

    std::map<std::string, sf::Texture> tileTextures;
};

}