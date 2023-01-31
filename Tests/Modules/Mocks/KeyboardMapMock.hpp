#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Config.hpp>

namespace FileMgmt
{

using ::testing::Test;

class KeyboardMapMock : public IKeyboardMap
{
public:
    MOCK_METHOD((const std::map<std::string, uint>&), getKeys, (), (const override));
	MOCK_METHOD(void, setKey, (const std::string& key, const uint val), (override));
};

}