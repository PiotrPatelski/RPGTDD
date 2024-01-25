#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <GameMapManager.hpp>
#include "AssetsManagerMock.hpp"

namespace Tiles
{

using namespace ::testing;

struct GameMapManagerTest : public testing::Test
{

};

TEST_F(GameMapManagerTest, gameMapManagerReturnsValidMapBuilder)
{
    NiceMock<FileMgmt::AssetsManagerMock> assetsManager;
    const sf::Texture texture;

    GameMapManager sut;

    EXPECT_CALL(assetsManager, getTexture(StrEq("TILESHEET"))).WillOnce(Return(&texture));
    ASSERT_NE(sut.createTileBuilder(assetsManager), nullptr);
}

}