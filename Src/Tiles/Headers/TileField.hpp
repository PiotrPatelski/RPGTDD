#pragma once
#include <SFML/Graphics.hpp>

namespace Types
{
class Window;
}

namespace Tiles
{

class Tile;

class TileField
{
public:
    TileField(const sf::Vector2i&);
    TileField(TileField&&);
    TileField(const TileField&) = delete;
    virtual ~TileField(){};
    virtual sf::Vector2i getPosition() const;
    virtual bool isEmpty() const;
    virtual bool isFull() const;
    virtual void pushTile(std::unique_ptr<Tile>);
    virtual void popTile ();
    // virtual void update();
    virtual void drawTo(Types::Window&);

    TileField& operator=(TileField&&);
    TileField& operator=(const TileField&) = delete;
private:
    std::vector<std::unique_ptr<Tile>> layers;
};

}