#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace Core
{

using ::testing::Test;
using testing::Return;

class WindowMock : public IWindow
{
public:
    MOCK_METHOD(bool, isActive, (), (override));
    MOCK_METHOD(bool, isCurrentlyFocused, (), (override));
    MOCK_METHOD(void, openWithSettings, (const GraphicsConfig&), (override));
    MOCK_METHOD(void, clear, (), (override));
    MOCK_METHOD(void, display, (), (override));
    MOCK_METHOD(void, handleSfmlEvents, (sf::Event), (override));
    MOCK_METHOD(void, close, (), (override));
};

}