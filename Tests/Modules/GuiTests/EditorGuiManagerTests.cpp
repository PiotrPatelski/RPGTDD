#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <EditorGuiManager.hpp>
#include <ButtonBuilderMock.hpp>
#include <ButtonMock.hpp>
#include <ButtonListMock.hpp>
#include <ButtonMenuBuilderMock.hpp>
#include <GuiActions.hpp>

namespace Gui
{

using namespace ::testing;

struct EditorGuiManagerTest : public ::testing::Test
{
    EditorGuiManagerTest()
    {
        ON_CALL(*pauseMenuBuilder, withTextContent(_)).WillByDefault(ReturnRef(*pauseMenuBuilder));
        ON_CALL(*pauseMenuBuilder, atPosition(_)).WillByDefault(ReturnRef(*pauseMenuBuilder));
        ON_CALL(*pauseMenuBuilder, withSize(_)).WillByDefault(ReturnRef(*pauseMenuBuilder));
        ON_CALL(*pauseMenuBuilder, withSection(_, _)).WillByDefault(ReturnRef(*pauseMenuBuilder));
        ON_CALL(*pauseMenuBuilder, build()).WillByDefault(Return(ByMove(std::make_unique<NiceMock<ButtonListMock>>())));
    }
    std::unique_ptr<NiceMock<ButtonMock>> saveButton = std::make_unique<NiceMock<ButtonMock>>();
    std::unique_ptr<NiceMock<ButtonMock>> loadButton = std::make_unique<NiceMock<ButtonMock>>();
    std::unique_ptr<NiceMock<ButtonMock>> exitButton = std::make_unique<NiceMock<ButtonMock>>();
    std::unique_ptr<NiceMock<ButtonMock>> resumeButton = std::make_unique<NiceMock<ButtonMock>>();
    std::unique_ptr<NiceMock<ButtonListMock>> pauseMenu = std::make_unique<NiceMock<ButtonListMock>>();
    std::unique_ptr<NiceMock<ButtonBuilderMock>> buttonBuilder = std::make_unique<NiceMock<ButtonBuilderMock>>();
    std::unique_ptr<NiceMock<ButtonMenuBuilderMock>> pauseMenuBuilder = std::make_unique<NiceMock<ButtonMenuBuilderMock>>();
    const sf::VideoMode resolution{480, 480};
};

TEST_F(EditorGuiManagerTest, editorGuiManagerCreatesGuiWithFourButtons)
{
    EXPECT_CALL(*pauseMenuBuilder, withTextContent(_)).WillOnce(ReturnRef(*pauseMenuBuilder));
    EXPECT_CALL(*pauseMenuBuilder, atPosition(_)).WillOnce(ReturnRef(*pauseMenuBuilder));
    EXPECT_CALL(*pauseMenuBuilder, withSize(_)).WillOnce(ReturnRef(*pauseMenuBuilder));
    EXPECT_CALL(*pauseMenuBuilder, withSection(_, _)).Times(4).WillRepeatedly(ReturnRef(*pauseMenuBuilder));
    EXPECT_CALL(*pauseMenuBuilder, build()).WillOnce(Return(ByMove(std::make_unique<NiceMock<ButtonListMock>>())));

    const sf::VideoMode resolution{480, 480};
    auto sut = std::make_unique<EditorGuiManager>(resolution, std::move(buttonBuilder), std::move(pauseMenuBuilder));
    auto gui = sut->createGui(sf::Font{});
}

TEST_F(EditorGuiManagerTest, editorGuiManagerCreatesFourSectionsWithGivenNamesAndActions)
{
    EXPECT_CALL(*pauseMenuBuilder, withSection(Optional(Property(&sf::Text::getString, StrEq("Save"))), _)).
        WillOnce(ReturnRef(*pauseMenuBuilder));
    EXPECT_CALL(*pauseMenuBuilder, withSection(Optional(Property(&sf::Text::getString, StrEq("Load"))), _)).
        WillOnce(ReturnRef(*pauseMenuBuilder));
    EXPECT_CALL(*pauseMenuBuilder, withSection(Optional(Property(&sf::Text::getString, StrEq("Exit"))), VariantWith<Events::GameAction>(_))).
        WillOnce(ReturnRef(*pauseMenuBuilder));
    EXPECT_CALL(*pauseMenuBuilder, withSection(Optional(Property(&sf::Text::getString, StrEq("Resume"))), VariantWith<Events::GameAction>(_))).
        WillOnce(ReturnRef(*pauseMenuBuilder));
    EXPECT_CALL(*pauseMenuBuilder, build()).WillOnce(Return(ByMove(std::move(pauseMenu))));
    const sf::VideoMode resolution{480, 480};
    auto sut = std::make_unique<EditorGuiManager>(resolution, std::move(buttonBuilder), std::move(pauseMenuBuilder));
    auto gui = sut->createGui(sf::Font{});
}

}