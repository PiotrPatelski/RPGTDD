#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <WindowBuilder.h>
#include "WindowMock.h"


namespace Core
{

using ::testing::Test;
using ::testing::Return;
using ::testing::NiceMock;
using ::testing::ByMove;

class WindowBuilderMock : public IWindowBuilder
{
public:

};

}