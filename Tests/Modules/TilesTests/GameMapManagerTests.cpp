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

TEST_F(GameMapManagerTest, createdObject)
{
    GameMapManager sut;
}

}