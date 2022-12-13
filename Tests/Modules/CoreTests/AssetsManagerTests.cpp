#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <AssetsManager.h>

#define TEST_PATH _PROJECT_ROOT_FOLDER"/TestResources"

namespace Core
{

using ::testing::NiceMock;
using ::testing::Test;

struct MainMenuAssetsManagerTest : public testing::Test
{

};

TEST_F(MainMenuAssetsManagerTest, mainMenuTextureThrowsWhenPathIsInvalid)
{
    auto sut = std::make_unique<MainMenuAssetsManager>();
    sut->setBuildPath("Invalid/Test/Path");
    EXPECT_THROW(sut->fetchTextureFromFile(), std::runtime_error);
}

TEST_F(MainMenuAssetsManagerTest, mainMenuTextureIsSetCorrectlyWhenValidPathIsProvided)
{
    auto sut = std::make_unique<MainMenuAssetsManager>();
    sut->setBuildPath(TEST_PATH);
    ASSERT_NO_THROW(sut->fetchTextureFromFile());
}

TEST_F(MainMenuAssetsManagerTest, mainMenuFontThrowsWhenPathIsInvalid)
{
    auto sut = std::make_unique<MainMenuAssetsManager>();
    sut->setBuildPath("Invalid/Test/Path");
    EXPECT_THROW(sut->fetchFontFromFile(), std::runtime_error);
}

TEST_F(MainMenuAssetsManagerTest, mainMenuFontIsSetCorrectlyWhenValidPathIsProvided)
{
    auto sut = std::make_unique<MainMenuAssetsManager>();
    sut->setBuildPath(TEST_PATH);
    ASSERT_NO_THROW(sut->fetchFontFromFile());
}

}