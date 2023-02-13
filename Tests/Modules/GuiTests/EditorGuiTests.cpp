#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <WindowMock.hpp>
#include <EditorGui.hpp>

namespace Gui
{

using namespace ::testing;

struct EditorGuiTest : public testing::Test
{
    std::unique_ptr<UserInterface> sut;
};


TEST_F(EditorGuiTest, emptyEditorGuiCreated)
{
    sut = std::make_unique<EditorGui>();
}

}