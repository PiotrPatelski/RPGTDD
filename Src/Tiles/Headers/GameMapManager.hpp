#pragma once
#include <TileMapManager.hpp>
#include <TileBuilder.hpp>

namespace Tiles
{

class TileMap;

class GameMapManager : public TileMapManager
{
public:
    GameMapManager() = default;
    virtual ~GameMapManager() = default;
    virtual std::unique_ptr<TileMap> createTileMap(const FileMgmt::AssetsManager&) override;
    virtual std::unique_ptr<TileBuilder> moveTileBuilder() override;
private:
    std::unique_ptr<TileBuilder> defaultTileBuilder;
};

}