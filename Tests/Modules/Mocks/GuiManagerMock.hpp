#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <GuiManager.hpp>

namespace Gui
{

using ::testing::Test;
using testing::Return;

class GuiManagerMock : public GuiManager
{
public:

    MOCK_METHOD(std::unique_ptr<Gui::UserInterface>, createGui, (const std::shared_ptr<sf::Font>), (override));
};

}