#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <EditorGuiManager.hpp>
#include <ButtonBuilderMock.hpp>

namespace Gui
{

using namespace ::testing;

struct EditorGuiManagerTest : public ::testing::Test
{

};

TEST_F(EditorGuiManagerTest, emptyEditorGuiManagerCreated)
{
    auto buttonBuilder = std::make_unique<NiceMock<ButtonBuilderMock>>();
    auto sut = std::make_unique<EditorGuiManager>(std::move(buttonBuilder));
}

}