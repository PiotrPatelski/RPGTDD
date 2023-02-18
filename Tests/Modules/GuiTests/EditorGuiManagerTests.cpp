#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <EditorGuiManager.hpp>
#include <ButtonBuilderMock.hpp>
#include <ButtonMock.hpp>
#include <GuiActions.hpp>

namespace Gui
{

using namespace ::testing;

struct EditorGuiManagerTest : public ::testing::Test
{
    std::unique_ptr<NiceMock<ButtonMock>> saveButton = std::make_unique<NiceMock<ButtonMock>>();
    std::unique_ptr<NiceMock<ButtonMock>> loadButton = std::make_unique<NiceMock<ButtonMock>>();
    std::unique_ptr<NiceMock<ButtonMock>> exitButton = std::make_unique<NiceMock<ButtonMock>>();
    std::unique_ptr<NiceMock<ButtonMock>> resumeButton = std::make_unique<NiceMock<ButtonMock>>();
};

TEST_F(EditorGuiManagerTest, editorGuiManagerCreatesGuiWithFourButtons)
{
    auto buttonBuilder = std::make_unique<NiceMock<ButtonBuilderMock>>();
    EXPECT_CALL(*buttonBuilder, withTextContent(_)).Times(4).WillRepeatedly(ReturnRef(*buttonBuilder));
    EXPECT_CALL(*buttonBuilder, atPosition(_, _)).Times(4).WillRepeatedly(ReturnRef(*buttonBuilder));
    EXPECT_CALL(*buttonBuilder, withSize(_, _)).Times(4).WillRepeatedly(ReturnRef(*buttonBuilder));
    EXPECT_CALL(*buttonBuilder, build())
        .WillOnce(Return(ByMove(std::move(saveButton))))
        .WillOnce(Return(ByMove(std::move(loadButton))))
        .WillOnce(Return(ByMove(std::move(exitButton))))
        .WillOnce(Return(ByMove(std::move(resumeButton))));
    const sf::VideoMode resolution{480, 480};
    auto sut = std::make_unique<EditorGuiManager>(std::move(buttonBuilder), resolution);
    auto gui = sut->createGui(sf::Font{});
}

}