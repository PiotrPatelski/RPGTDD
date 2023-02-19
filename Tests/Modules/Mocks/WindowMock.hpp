#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Window.hpp>

namespace Types
{

using ::testing::Test;
using testing::Return;

class WindowMock : public IWindow
{
public:
    MOCK_METHOD(bool, isActive, (), (const, override));
    MOCK_METHOD(bool, isCurrentlyFocused, (), (const, override));
    MOCK_METHOD(void, openWithSettings, (const FileMgmt::GraphicsConfig&), (override));
    MOCK_METHOD(sf::Vector2i, getMousePosition, (), (const, override));
    MOCK_METHOD(void, clear, (), (override));
    MOCK_METHOD(void, draw, (const sf::Drawable&), (override));
    MOCK_METHOD(void, display, (), (override));
    MOCK_METHOD(void, handleSfmlEvents, (sf::Event), (override));
    MOCK_METHOD(void, close, (), (override));
};

}