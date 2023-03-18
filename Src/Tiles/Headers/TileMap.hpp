#pragma once
#include <SFML/Graphics.hpp>

namespace Tiles
{

class Tile;

class TileMap
{
public:
    TileMap(const uint, const uint, const uint);
    virtual ~TileMap() = default;
    virtual bool isEmptyAt(const sf::Vector2i&) const;
    virtual bool isValidPosition(const sf::Vector2i&) const;
    virtual void addTile(std::unique_ptr<Tile>);
    virtual void removeTile (const sf::Vector2i&);
private:
    const uint tileBoxSize;
	std::vector<
		std::vector<
			std::unique_ptr<Tile> > > map;
    uint calculateIndex(const uint pixelPos) const;
};

}