#pragma once
#include <TileMapManager.hpp>
#include <TileBuilder.hpp>

namespace Tiles
{

class TileMap;

class GameMapManager : public TileMapManager
{
public:
    GameMapManager();
    virtual ~GameMapManager() = default;
    virtual std::unique_ptr<TileMap> createTileMap() override;
    virtual std::unique_ptr<TileBuilder> createTileBuilder(
        const FileMgmt::AssetsManager&,
        const FileMgmt::IConfigManager&) override;
private:
    std::unique_ptr<TileBuilder> defaultTileBuilder;
    const uint tileBoxSize;
};

}