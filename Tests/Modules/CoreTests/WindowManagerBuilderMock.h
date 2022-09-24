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

};



}