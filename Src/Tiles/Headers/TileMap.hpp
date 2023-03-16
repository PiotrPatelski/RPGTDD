#pragma once

namespace Tiles
{

class Tile;

class TileMap
{
public:
    TileMap() = default;
    virtual ~TileMap() = default;
    virtual void addTile(std::unique_ptr<Tile>) {};
};

}