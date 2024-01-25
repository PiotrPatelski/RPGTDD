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
    MOCK_METHOD(std::unique_ptr<TileMap>, createTileMap, (), (override));
    MOCK_METHOD(std::unique_ptr<TileBuilder>, createTileBuilder, (const FileMgmt::AssetsManager&), (override));
};

}