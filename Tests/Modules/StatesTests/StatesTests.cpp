#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <State.h>

namespace States
{

using ::testing::NiceMock;
using ::testing::Test;
using ::testing::Return;
using ::testing::InSequence;
using ::testing::_;

struct StatesTest : public testing::Test
{
    std::unique_ptr<IState> sut = std::make_unique<State>();
};

TEST_F(StatesTest, stateIsDoneWhenSetAsDone)
{
    sut->markAsDone();
    ASSERT_TRUE(sut->isDone());
}

}