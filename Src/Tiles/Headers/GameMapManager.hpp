#pragma once
#include <TileMapManager.hpp>

namespace Tiles
{

class TileMap;

class GameMapManager : public TileMapManager
{
public:
    GameMapManager() = default;
    virtual ~GameMapManager() = default;
    virtual std::unique_ptr<TileMap> createTileMap(const FileMgmt::AssetsManager&) override;
};

}