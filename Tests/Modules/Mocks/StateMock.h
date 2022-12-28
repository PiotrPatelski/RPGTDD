#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <State.h>

namespace States
{

using ::testing::Test;
using testing::Return;

class StateMock : public IState
{
public:
    MOCK_METHOD(std::unique_ptr<IState>, getNextState, (), (override));
    MOCK_METHOD(void, drawOutput, (Core::IWindow&), (override));
    MOCK_METHOD(void, update, (const sf::Vector2i&, const float), (override));
    MOCK_METHOD(const bool, isDone, (), (const override));
    MOCK_METHOD(void, markAsDone, (), (override));

};

}