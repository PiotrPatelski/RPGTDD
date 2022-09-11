#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Game.h>


namespace Core
{

using ::testing::Test;

class GameMock : public IGame
{
public:
    MOCK_METHOD(bool, getIsRunning, (), (override));
    MOCK_METHOD(void, setIsRunning, (bool), (override));
    MOCK_METHOD(void, update, (), (override));
    MOCK_METHOD(void, updateDeltaTime, (), (override));
    MOCK_METHOD(void, render, (), (override));
};    

}
