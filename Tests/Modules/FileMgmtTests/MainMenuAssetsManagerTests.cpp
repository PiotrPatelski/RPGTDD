#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <MainMenuAssetsManager.hpp>

#define TEST_PATH _PROJECT_ROOT_FOLDER"/TestResources"

namespace FileMgmt
{

using ::testing::NiceMock;
using ::testing::Test;

struct MainMenuAssetsManagerTest : public testing::Test
{

};

TEST_F(MainMenuAssetsManagerTest, mainMenuAssetsManagerThrowsWhenPathIsInvalid)
{
    AssetsManager::setBuildPath("Invalid/Test/Path");
    EXPECT_THROW(std::make_unique<MainMenuAssetsManager>(), std::runtime_error);
}

TEST_F(MainMenuAssetsManagerTest, mainMenuAssetsManagerDoesntThrowWhenValidPathIsProvided)
{
    AssetsManager::setBuildPath(TEST_PATH);
    ASSERT_NO_THROW(std::make_unique<MainMenuAssetsManager>());
}

TEST_F(MainMenuAssetsManagerTest, mainMenuAssetsManagerGetsValidFontWhenValidPathIsProvided)
{
    AssetsManager::setBuildPath(TEST_PATH);
    auto sut = std::make_unique<MainMenuAssetsManager>();
    ASSERT_NO_THROW(sut->getFont("MENU_BUTTON"));
    ASSERT_EQ(sut->getFont("MENU_BUTTON").getInfo().family, "xBONES");
}

}