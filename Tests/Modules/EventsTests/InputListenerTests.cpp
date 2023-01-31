#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <InputListener.hpp>
#include <KeyboardMapMock.hpp>
#include <ConfigManagerMock.hpp>

namespace Events
{

using namespace ::testing;

struct InputListenerTest : public testing::Test
{
    std::shared_ptr<NiceMock<Core::ConfigManagerMock>> configManager = std::make_shared<NiceMock<Core::ConfigManagerMock>>();
};

TEST_F(InputListenerTest, inputListenerGetsActiveActionWithNoThrowWhenValidKeysAreChecked)
{
    NiceMock<FileMgmt::KeyboardMapMock> availableKeys;
    std::map<std::string, uint> keyIds;
    keyIds["CLOSE"] = 0;
    EXPECT_CALL(availableKeys, getKeys()).WillOnce(ReturnRef(keyIds));
    InputListener sut(availableKeys);
    EXPECT_NO_THROW(sut.getActiveAction());
}

TEST_F(InputListenerTest, inputListenerThrowsOnGetActiveActionWhenCheckedKeysAreNotFound)
{
    NiceMock<FileMgmt::KeyboardMapMock> availableKeys;
    std::map<std::string, uint> keyIds;
    keyIds["UNEXPECTED_KEY"] = 0;
    EXPECT_CALL(availableKeys, getKeys()).WillOnce(ReturnRef(keyIds));
    InputListener sut(availableKeys);
    EXPECT_THROW(sut.getActiveAction(), std::out_of_range);
}

}