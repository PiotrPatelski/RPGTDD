#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <GuiManager.hpp>

namespace Gui
{

using namespace ::testing;

class UserInterfaceMock : public IUserInterface
{
public:
    MOCK_METHOD(void, addButton, (std::shared_ptr<IButton>, Events::StateAction), (override));
    MOCK_METHOD(std::optional<Events::StateAction>, getActiveAction, (), (override));
    MOCK_METHOD(void, drawTo, (Core::IWindow&), (override));
    MOCK_METHOD(void, update, (const Core::IWindow&), (override));
};

}