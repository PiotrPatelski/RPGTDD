#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <TileMapManager.hpp>

namespace Tiles
{

using namespace ::testing;

class TileMapManagerMock : public TileMapManager
{
public:
    MOCK_METHOD(std::unique_ptr<TileMap>, createTileMap, (const FileMgmt::AssetsManager&), (override));
    MOCK_METHOD(std::unique_ptr<TileBuilder>, moveTileBuilder, (), (override));
};

}