#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <MenuState.hpp>
#include <MapState.hpp>
#include <ConfigManagerMock.hpp>
#include <AssetsManagerMock.hpp>
#include <GuiManagerMock.hpp>
#include <InputListenerMock.hpp>
#include <WindowMock.hpp>

namespace States
{

using namespace ::testing;

class StateMock : public IState
{
public:
    MOCK_METHOD(void, finishState, (), ());
    MOCK_METHOD(void, setNextState, (std::unique_ptr<IState>), (override));
    MOCK_METHOD(std::unique_ptr<IState>, getNextState, (), (override));
    MOCK_METHOD(const bool, isReadyToChange, (), (const override));
    MOCK_METHOD(std::shared_ptr<Core::IConfigManager>, getConfig, (), ());
    MOCK_METHOD(void, drawOutput, (::Types::Window&), (override));
    MOCK_METHOD(void, update, (const ::Types::Window&, const float), (override));
};

class MenuStateMock : public MenuState
{
public:
    MenuStateMock()
    : MenuState(
        std::make_shared<NiceMock<Core::ConfigManagerMock>>(),
        std::make_unique<NiceMock<FileMgmt::AssetsManagerMock>>())
    {}
    MOCK_METHOD(void, finishState, (), ());
    MOCK_METHOD(void, setNextState, (std::unique_ptr<IState>), (override));
    MOCK_METHOD(std::unique_ptr<IState>, getNextState, (), (override));
    MOCK_METHOD(const bool, isReadyToChange, (), (const override));
    MOCK_METHOD(std::shared_ptr<Core::IConfigManager>, getConfig, (), ());
    MOCK_METHOD(void, drawOutput, (::Types::Window&), (override));
    MOCK_METHOD(void, update, (const ::Types::Window&, const float), (override));
};

class MapStateMock : public MapState
{
public:
    MapStateMock()
    : MapState(
        std::make_shared<NiceMock<Core::ConfigManagerMock>>(),
        std::make_unique<NiceMock<FileMgmt::AssetsManagerMock>>())
    {}
    MOCK_METHOD(void, finishState, (), ());
    MOCK_METHOD(void, setNextState, (std::unique_ptr<IState>), (override));
    MOCK_METHOD(std::unique_ptr<IState>, getNextState, (), (override));
    MOCK_METHOD(const bool, isReadyToChange, (), (const override));
    MOCK_METHOD(std::shared_ptr<Core::IConfigManager>, getConfig, (), ());
    MOCK_METHOD(void, drawOutput, (::Types::Window&), (override));
    MOCK_METHOD(void, update, (const ::Types::Window&, const float), (override));
    MOCK_METHOD(void, togglePause, (), (override));
    MOCK_METHOD(void, tryTileAdditionAt, (const sf::Vector2i&), (override));
    MOCK_METHOD(void, tryTileRemovalAt, (const sf::Vector2i&), (override));
};

}