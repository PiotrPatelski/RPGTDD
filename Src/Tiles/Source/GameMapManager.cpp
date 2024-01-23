#include <GameMapManager.hpp>
#include <TileMap.hpp>

namespace Tiles
{
GameMapManager::GameMapManager()
: defaultTileBuilder(std::make_unique<TileBuilder>())
{

}

std::unique_ptr<TileMap> GameMapManager::createTileMap(const FileMgmt::AssetsManager&)
{
    const float tileBoxSize = 64.f;
    const uint amountOfTilesOnX = 10;
    const uint amountOfTilesOnY = 10;
    return std::make_unique<TileMap>(tileBoxSize, amountOfTilesOnX, amountOfTilesOnY);
}

std::unique_ptr<TileBuilder> GameMapManager::moveTileBuilder()
{
    return std::move(defaultTileBuilder);
}

}