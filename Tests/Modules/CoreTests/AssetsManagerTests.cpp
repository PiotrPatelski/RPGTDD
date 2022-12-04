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

TEST_F(MainMenuAssetsManagerTest, MainMenuTextureThrowsWhenPathIsInvalid)
{
    const std::string pathToFile = "Invalid/Test/Path";
    auto sut = std::make_unique<MainMenuAssetsManager>(pathToFile);
    EXPECT_THROW(sut->fetchTextureFromFile(), std::runtime_error);
}

TEST_F(MainMenuAssetsManagerTest, MainMenuTextureIsSetCorrectlyWhenValidPathIsProvided)
{
    const std::string pathToFile = TEST_PATH;
    auto sut = std::make_unique<MainMenuAssetsManager>(pathToFile);
    ASSERT_NO_THROW(sut->fetchTextureFromFile());
}

TEST_F(MainMenuAssetsManagerTest, MainMenuFontThrowsWhenPathIsInvalid)
{
    const std::string pathToFile = "Invalid/Test/Path";
    auto sut = std::make_unique<MainMenuAssetsManager>(pathToFile);
    EXPECT_THROW(sut->fetchFontFromFile(), std::runtime_error);
}

TEST_F(MainMenuAssetsManagerTest, MainMenuFontIsSetCorrectlyWhenValidPathIsProvided)
{
    const std::string pathToFile = TEST_PATH;
    auto sut = std::make_unique<MainMenuAssetsManager>(pathToFile);
    ASSERT_NO_THROW(sut->fetchFontFromFile());
}

}