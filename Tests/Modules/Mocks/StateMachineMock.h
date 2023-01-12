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
    MOCK_METHOD(bool, isAnyStateActive, (), (override));
    MOCK_METHOD(std::shared_ptr<States::IState>, getCurrentState, (), (override));
    MOCK_METHOD(void, setState, (std::shared_ptr<States::IState>), (override));
};

}