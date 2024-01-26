#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <GameMapManager.hpp>
#include "AssetsManagerMock.hpp"
#include "ConfigManagerMock.hpp"

namespace Tiles
{

using namespace ::testing;

struct GameMapManagerTest : public testing::Test
{

};

TEST_F(GameMapManagerTest, gameMapManagerReturnsValidMapBuilder)
{
    NiceMock<FileMgmt::AssetsManagerMock> assetsManager;
    NiceMock<FileMgmt::ConfigManagerMock> configManager;
    const sf::Texture texture;
    const std::vector<std::string> tileIds;

    GameMapManager sut;

    EXPECT_CALL(assetsManager, getTexture(StrEq("TILESHEET"))).WillOnce(Return(&texture));
    EXPECT_CALL(configManager, getTileIdConfig()).WillOnce(ReturnRef(tileIds));
    ASSERT_NE(sut.createTileBuilder(assetsManager, configManager), nullptr);
}

}