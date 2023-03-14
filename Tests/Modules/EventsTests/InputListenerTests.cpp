#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <InputListener.hpp>
#include <KeyboardMapMock.hpp>
#include <ConfigManagerMock.hpp>
#include <MouseEventListenerMock.hpp>

namespace Events
{

using namespace ::testing;

struct MenuInputListenerTest : public testing::Test
{};

TEST_F(MenuInputListenerTest, inputListenerGetsActiveActionWhenValidKeysArePressed)
{
    auto availableKeys = std::make_unique<NiceMock<FileMgmt::KeyboardMapMock>>();
    EXPECT_CALL(*availableKeys, isPressedAt(StrEq("CLOSE"))).WillOnce(Return(true));
    FileMgmt::KeyboardConfig config;
    config.setMainMenuKeyboard(std::move(availableKeys));
    MenuInputListener sut(config);
    ASSERT_NE(sut.getKeyboardAction(), std::nullopt);
}

TEST_F(MenuInputListenerTest, inputListenerReturnsNulloptOngetKeyboardActionWhenCheckedKeysAreNotPressed)
{
    auto availableKeys = std::make_unique<NiceMock<FileMgmt::KeyboardMapMock>>();
    EXPECT_CALL(*availableKeys, isPressedAt(StrEq("CLOSE"))).WillOnce(Return(false));
    FileMgmt::KeyboardConfig config;
    config.setMainMenuKeyboard(std::move(availableKeys));
    MenuInputListener sut(config);
    EXPECT_EQ(sut.getKeyboardAction(), std::nullopt);
}

struct EditorInputListenerTest : public testing::Test
{
    FileMgmt::KeyboardConfig config;
    std::unique_ptr<NiceMock<Events::MouseEventListenerMock>> mouseListener = std::make_unique<NiceMock<Events::MouseEventListenerMock>>();
};

TEST_F(EditorInputListenerTest, inputListenerGetsKeyActionWhenValidKeysArePressed)
{
    auto availableKeys = std::make_unique<NiceMock<FileMgmt::KeyboardMapMock>>();
    EXPECT_CALL(*availableKeys, isPressedAt(StrEq("PAUSE"))).WillOnce(Return(true));

    config.setEditorKeyboard(std::move(availableKeys));
    EditorInputListener sut(config, nullptr);
    auto result = sut.getKeyboardAction();
    ASSERT_NE(result, std::nullopt);
    EXPECT_TRUE(std::holds_alternative<Events::GameAction>(result.value()));
}

TEST_F(EditorInputListenerTest, inputListenerReturnsNulloptOngetKeyboardActionWhenCheckedKeysAreNotPressed)
{
    auto availableKeys = std::make_unique<NiceMock<FileMgmt::KeyboardMapMock>>();
    EXPECT_CALL(*availableKeys, isPressedAt(StrEq("PAUSE"))).WillOnce(Return(false));

    config.setEditorKeyboard(std::move(availableKeys));
    EditorInputListener sut(config, nullptr);
    EXPECT_EQ(sut.getKeyboardAction(), std::nullopt);
}

TEST_F(EditorInputListenerTest, inputListenerGetsMouseActionWhenMouseIsPressed)
{
    const sf::Vector2i currentMousePos{0, 0};

    EXPECT_CALL(*mouseListener, isPressed()).WillOnce(Return(true));
    EditorInputListener sut(config, std::move(mouseListener));
    auto result = sut.getMouseAction(currentMousePos);
    ASSERT_NE(result, std::nullopt);
    EXPECT_TRUE(std::holds_alternative<Events::GameAction>(result.value()));
}

TEST_F(EditorInputListenerTest, inputListenerGetsNulloptWhenMouseIsNotPressed)
{
    const sf::Vector2i currentMousePos{0, 0};

    EXPECT_CALL(*mouseListener, isPressed()).WillOnce(Return(false));
    EditorInputListener sut(config, std::move(mouseListener));
    EXPECT_EQ(sut.getMouseAction(currentMousePos), std::nullopt);
}

}