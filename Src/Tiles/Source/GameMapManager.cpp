#include <GameMapManager.hpp>
#include <TileMap.hpp>
#include <AssetsManager.hpp>
#include <ConfigManager.hpp>

namespace Tiles
{
GameMapManager::GameMapManager()
{

}

std::unique_ptr<TileMap> GameMapManager::createTileMap()
{
    const float tileBoxSize = 64.f;
    const uint amountOfTilesOnX = 10;
    const uint amountOfTilesOnY = 10;
    return std::make_unique<TileMap>(tileBoxSize, amountOfTilesOnX, amountOfTilesOnY);
}

std::unique_ptr<TileBuilder> GameMapManager::createTileBuilder(
    const FileMgmt::AssetsManager& assetsManager,
    const FileMgmt::IConfigManager& configManager)
{
    return std::make_unique<DefaultTileBuilder>(
        assetsManager.getTexture("TILESHEET"),
        configManager.getTileIdConfig());
}

}