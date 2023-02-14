#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <GuiActions.hpp>


namespace Events
{

class GuiActionMock : public GuiAction
{
public:
    MOCK_METHOD(void, execute, (Gui::MenuGui&), (override));
    MOCK_METHOD(void, execute, (Gui::EditorGui&), (override));
    MOCK_METHOD(void, execute, (Gui::GameGui&), (override));

};

}