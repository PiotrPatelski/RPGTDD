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
    MOCK_METHOD(void, setBuildPath, (const std::string&), (override));
    MOCK_METHOD(std::string, getBuildPath, (), (const, override));
    MOCK_METHOD(bool, isWindowOpen, (), (override));
    MOCK_METHOD(void, fetchGraphicsSettings, (IIniParser&), (override));
    MOCK_METHOD(void, fetchPlayerInputSettings, (IIniParser&), (override));
    MOCK_METHOD(void, startStateMachine, (), (override));
    MOCK_METHOD(void, openWindow, (), (override));
    MOCK_METHOD(void, update, (), (override));
    MOCK_METHOD(void, updateClock, (), (override));
    MOCK_METHOD(void, render, (), (override));
};    

}
