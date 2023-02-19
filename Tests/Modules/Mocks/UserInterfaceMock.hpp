#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <GuiManager.hpp>
#include <GuiActions.hpp>

namespace Gui
{

using namespace ::testing;

class UserInterfaceMock : public UserInterface
{
public:
    MOCK_METHOD(void, acceptRequest, (Events::GuiAction&), (override));
    MOCK_METHOD(void, addButton, (std::unique_ptr<Button>, Events::StateAction), (override));
    MOCK_METHOD(void, addButtonList, (std::unique_ptr<ButtonList>), (override));
    MOCK_METHOD(std::optional<Events::StateAction>, getActiveAction, (), (override));
    MOCK_METHOD(void, drawTo, (::Types::IWindow&), (override));
    MOCK_METHOD(void, update, (const sf::Vector2i&), (override));
};

}