#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <SFML/Window.hpp>
#include <Window.h>

namespace Core
{

struct WindowTest : public testing::Test
{    
    std::unique_ptr<IWindow> sut = std::make_unique<Window>();
    GraphicsConfig graphicsConfig{"TEST", {21,37}, 0, 0, 0, sf::ContextSettings{}};
};

TEST_F(WindowTest, windowIsNotActiveUponCreation)
{
    ASSERT_FALSE(sut->isActive());
}

TEST_F(WindowTest, windowIsActiveWhenLaunched)
{
    sut->openWithSettings(graphicsConfig);
    ASSERT_TRUE(sut->isActive());
}

TEST_F(WindowTest, windowRemainsActiveWhenNoClosingEventAppearedDuringUpdate)
{
    sut->openWithSettings(graphicsConfig);
    sf::Event event;
    sut->handleSfmlEvents(event);
    ASSERT_TRUE(sut->isActive());
}

TEST_F(WindowTest, windowIsNotActiveWhenClosed)
{
    sut->openWithSettings(graphicsConfig);
    sut->close();
    ASSERT_FALSE(sut->isActive());
}

TEST_F(WindowTest, closingWindowThrowsWhenWindowIsNotOpen)
{
    ASSERT_THROW(sut->close(), std::runtime_error);
}

TEST_F(WindowTest, handlingSfmlEventsThrowsWhenWindowIsNotOpen)
{
    ASSERT_THROW(sut->handleSfmlEvents(sf::Event{}), std::runtime_error);
}

}