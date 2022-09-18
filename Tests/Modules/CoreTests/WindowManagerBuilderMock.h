#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <WindowManagerBuilder.h>
#include "WindowManagerMock.h"


namespace Core
{

using ::testing::Test;
using ::testing::Return;
using ::testing::NiceMock;
using ::testing::ByMove;

class WindowManagerBuilderMock : public IWindowManagerBuilder
{
public:
    // WindowManagerBuilderMock()
    // {
    //     ON_CALL(*this, build).WillByDefault(Return(ByMove(std::make_unique<WindowManagerMock>())));
    // }
    // MOCK_METHOD(std::unique_ptr<IWindowManager>, build, (), (override));
    std::unique_ptr<IWindowManager> build() override
    {
        return std::make_unique<WindowManagerMock>();
    }
};



}