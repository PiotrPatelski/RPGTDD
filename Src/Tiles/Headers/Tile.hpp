#pragma once

namespace Tiles
{

class Tile
{
public:
    Tile() = default;
    virtual ~Tile() = default;
    virtual sf::Vector2i getPosition() const {return {0, 0};}
};

}