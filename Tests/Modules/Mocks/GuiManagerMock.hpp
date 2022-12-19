#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <GuiManager.hpp>

namespace Gui
{

using ::testing::Test;
using testing::Return;

class MainMenuGuiManagerMock : public MainMenuGuiManager
{
public:
    MainMenuGuiManagerMock()
    : MainMenuGuiManager(sf::VideoMode()){}
    MOCK_METHOD((std::map<std::string, std::unique_ptr<IButton>>), createButtons, (const sf::Font&), (override));

};

}