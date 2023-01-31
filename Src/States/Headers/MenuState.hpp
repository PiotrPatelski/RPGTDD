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
        std::shared_ptr<Core::IConfigManager> configManager,
        std::unique_ptr<FileMgmt::IAssetsManager> assetsManager)
    : State(configManager, std::move(assetsManager)){}
    virtual ~MenuState(){}
};

}