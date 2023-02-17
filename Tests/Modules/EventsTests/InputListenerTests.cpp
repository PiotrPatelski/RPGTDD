#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <InputListener.hpp>
#include <KeyboardMapMock.hpp>
#include <ConfigManagerMock.hpp>

namespace Events
{

using namespace ::testing;

struct MenuInputListenerTest : public testing::Test
{
    std::shared_ptr<NiceMock<Core::ConfigManagerMock>> configManager = std::make_shared<NiceMock<Core::ConfigManagerMock>>();
};

TEST_F(MenuInputListenerTest, inputListenerGetsActiveActionWithNoThrowWhenValidKeysAreChecked)
{
    auto availableKeys = std::make_unique<NiceMock<FileMgmt::KeyboardMapMock>>();
    EXPECT_CALL(*availableKeys, isPressedAt(StrEq("CLOSE"))).WillOnce(Return(true));
    FileMgmt::KeyboardConfig config;
    config.setMainMenuKeyboard(std::move(availableKeys));
    MenuInputListener sut(config);
    ASSERT_NE(sut.getActiveAction(), std::nullopt);
}

TEST_F(MenuInputListenerTest, inputListenerThrowsOnGetActiveActionWhenCheckedKeysAreNotFound)
{
    auto availableKeys = std::make_unique<NiceMock<FileMgmt::KeyboardMapMock>>();
    EXPECT_CALL(*availableKeys, isPressedAt(StrEq("CLOSE"))).WillOnce(Return(false));
    FileMgmt::KeyboardConfig config;
    config.setMainMenuKeyboard(std::move(availableKeys));
    MenuInputListener sut(config);
    EXPECT_EQ(sut.getActiveAction(), std::nullopt);
}

}