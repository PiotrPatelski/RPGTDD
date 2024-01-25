#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <EditorAssetsManager.hpp>

#define TEST_PATH _PROJECT_ROOT_FOLDER"/TestResources"

namespace FileMgmt
{

using ::testing::NiceMock;
using ::testing::Test;

struct EditorAssetsManagerTest : public testing::Test
{

};

TEST_F(EditorAssetsManagerTest, editorAssetsManagerThrowsWhenPathIsInvalid)
{
    AssetsManager::setBuildPath("Invalid/Test/Path");
    EXPECT_THROW(std::make_unique<EditorAssetsManager>(), std::runtime_error);
}

TEST_F(EditorAssetsManagerTest, editorAssetsManagerDoesntThrowWhenValidPathIsProvided)
{
    AssetsManager::setBuildPath(TEST_PATH);
    ASSERT_NO_THROW(std::make_unique<EditorAssetsManager>());
}

TEST_F(EditorAssetsManagerTest, editorAssetsManagerGetsValidFontWhenValidPathIsProvided)
{
    AssetsManager::setBuildPath(TEST_PATH);
    auto sut = std::make_unique<EditorAssetsManager>();
    ASSERT_NO_THROW(sut->getFont("MENU_BUTTON"));
    ASSERT_EQ(sut->getFont("MENU_BUTTON").getInfo().family, "xBONES");
}

TEST_F(EditorAssetsManagerTest, editorAssetsManagerGetsValidTextureWhenValidPathIsProvided)
{
    AssetsManager::setBuildPath(TEST_PATH);
    auto sut = std::make_unique<EditorAssetsManager>();
    ASSERT_NO_THROW(sut->getTexture("TILESHEET"));
}

}