#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <StateMachine.h>


namespace Core
{

class StateMachineMock : public IStateMachine
{
public:
    MOCK_METHOD(void, update, (const sf::Vector2i&, const float), (override));
    MOCK_METHOD(bool, isNoStateActive, (), (override));
    MOCK_METHOD(std::shared_ptr<States::IState>, getCurrentState, (), (override));
    MOCK_METHOD(void, runState, (std::shared_ptr<States::IState>), (override));
};

}