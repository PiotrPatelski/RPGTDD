#include <GameMapManager.hpp>
#include <TileMap.hpp>

namespace Tiles
{

std::unique_ptr<TileMap> GameMapManager::createTileMap(const FileMgmt::AssetsManager&)
{
    return std::make_unique<TileMap>();
}

}