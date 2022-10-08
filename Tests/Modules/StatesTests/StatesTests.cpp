#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace States
{

using ::testing::NiceMock;
using ::testing::Test;
using ::testing::Return;
using ::testing::InSequence;
using ::testing::_;

struct StatesTest : public testing::Test
{
    
};

TEST_F(StatesTest, dummyTest)
{
    ASSERT_TRUE(true);
}

}