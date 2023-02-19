#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <AssetsManager.hpp>
#include <ButtonMock.hpp>
#include <WindowMock.hpp>
#include <ButtonBuilderMock.hpp>
#include <ButtonListBuilderMock.hpp>
#include <UserInterface.hpp>

#define TEST_PATH _PROJECT_ROOT_FOLDER"/TestResources"

namespace Gui
{

struct GuiManagerFixture : public testing::Test
{
    GuiManagerFixture()
    {
        FileMgmt::AssetsManager::setBuildPath(TEST_PATH);
        buttonBuilder = std::make_unique<testing::NiceMock<ButtonBuilderMock>>();
        dropDownListBuilder = std::make_unique<testing::NiceMock<ButtonListBuilderMock>>();
        ON_CALL(*buttonBuilder, withTextContent(testing::_)).WillByDefault(ReturnRef(*buttonBuilder));
        ON_CALL(*buttonBuilder, atPosition(testing::_)).WillByDefault(ReturnRef(*buttonBuilder));
        ON_CALL(*buttonBuilder, withSize(testing::_)).WillByDefault(ReturnRef(*buttonBuilder));
        ON_CALL(*dropDownListBuilder, withTriggerButton(testing::_)).WillByDefault(ReturnRef(*dropDownListBuilder));
        ON_CALL(*dropDownListBuilder, withTextContent(testing::_)).WillByDefault(ReturnRef(*dropDownListBuilder));
        ON_CALL(*dropDownListBuilder, withSection(testing::_, testing::_)).WillByDefault(ReturnRef(*dropDownListBuilder));
    }
    std::unique_ptr<testing::NiceMock<ButtonBuilderMock>> buttonBuilder;
    std::unique_ptr<testing::NiceMock<ButtonListBuilderMock>> dropDownListBuilder;
    std::unique_ptr<UserInterface> sut;
    testing::NiceMock<::Types::WindowMock> window;
    sf::VideoMode resolution{480, 480};
    ::Types::Background dummyBackground{
        VectorMath::ScreenPercentagePoint{resolution, {0,0}},
        VectorMath::ScreenPercentagePoint{resolution, {0,0}}};
};

}