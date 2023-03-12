#pragma once

namespace FileMgmt
{
class AssetsManager;
}

namespace Tiles
{

class TileMap;

class TileMapManager
{
public:
    TileMapManager() = default;
    virtual ~TileMapManager() = default;
    virtual std::unique_ptr<TileMap> createTileMap(const FileMgmt::AssetsManager&) = 0;
};

}