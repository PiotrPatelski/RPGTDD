#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Config.hpp>

namespace FileMgmt
{

using ::testing::Test;

class KeyboardMapMock : public KeyboardMap
{
public:
    MOCK_METHOD((const uint), getKey, (const std::string&), (const override));
	MOCK_METHOD(void, setKey, (const std::string& key, const uint val), (override));
	MOCK_METHOD((const bool), isPressedAt, (const std::string&), (const, override));
};

}