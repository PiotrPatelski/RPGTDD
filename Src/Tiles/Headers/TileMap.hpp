#pragma once
#include <SFML/Graphics.hpp>

namespace Types
{
class Window;
}

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
    virtual void update();
    virtual void drawTo(Types::Window&);
private:
    const uint tileBoxSize;
	std::vector<
		std::vector<
			std::unique_ptr<Tile> > > map;
    uint calculateIndex(const uint pixelPos) const;
};

}