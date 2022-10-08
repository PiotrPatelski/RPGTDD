#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Game.h>

namespace Core
{

using ::testing::Test;

class GameMock : public IGame
{
public:
    MOCK_METHOD(bool, isWindowOpen, (), (override));
    MOCK_METHOD(void, startStateMachine, (), (override));
    MOCK_METHOD(void, openWindow, (), (override));
    MOCK_METHOD(void, update, (), (override));
    MOCK_METHOD(void, updateDeltaTime, (), (override));
    MOCK_METHOD(void, render, (), (override));
};    

}
