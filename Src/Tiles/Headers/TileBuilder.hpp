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
    virtual std::unique_ptr<Tile> build(const std::string&) = 0;
};

class DefaultTileBuilder : public TileBuilder
{
public:
    DefaultTileBuilder(const sf::Texture*, const std::vector<std::string>&, const uint);
    virtual ~DefaultTileBuilder()
    {}

    virtual DefaultTileBuilder& atPosition(const sf::Vector2i&);
    virtual std::unique_ptr<Tile> build(const std::string&);
private:
    void mapIdsToTextureFields(const std::vector<std::string>&, const sf::Vector2u&);
    sf::Vector2i currentPosition;
    const sf::Texture* tileTextureSheet;
    const int tileBoxSize;
    std::map<std::string, sf::IntRect> tileTextures;
};

}