#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Button.hpp>

namespace Gui
{

struct MainMenuButtonTest : public testing::Test
{
    std::unique_ptr<IButton> sut = std::make_unique<MainMenuButton>(
        sf::Vector2f(0, 0),
        sf::Vector2f(0, 0),
        "Test",
        sf::Font{});
};

TEST_F(MainMenuButtonTest, buttonWillReturnItsTextContent)
{
    ASSERT_EQ(sut->getTextContent(), "Test");
}

}