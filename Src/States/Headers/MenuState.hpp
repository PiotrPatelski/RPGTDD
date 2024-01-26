#pragma once

#include <State.hpp>
#include <ConfigManager.hpp>
#include <AssetsManager.hpp>

namespace States
{

class MenuState : public State
{
public:
    MenuState(
        std::shared_ptr<FileMgmt::IConfigManager> configManager,
        std::unique_ptr<FileMgmt::AssetsManager> assetsManager)
    : State(configManager, std::move(assetsManager)){}
    virtual ~MenuState(){}
};

}