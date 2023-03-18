#pragma once

namespace Types
{
class Window;
}

namespace Tiles
{

class Tile
{
public:
    Tile() = default;
    virtual ~Tile() = default;
    virtual sf::Vector2i getPosition() const {return {0, 0};}
    virtual void drawTo(Types::Window&) {}
};

}