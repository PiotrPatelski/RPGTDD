#pragma once

#include <State.hpp>
#include <ConfigManager.hpp>
#include <AssetsManager.hpp>

namespace States
{

class MapState : public State
{
public:
    MapState(
        std::shared_ptr<Core::IConfigManager> configManager,
        std::unique_ptr<FileMgmt::AssetsManager> assetsManager)
    : State(configManager, std::move(assetsManager)),
      paused{false}{}
    virtual ~MapState(){}
    virtual void togglePause() = 0;
    virtual void addTileAt(const sf::Vector2i&) = 0;
    virtual void removeTileAt(const sf::Vector2i&) = 0;
protected:
    bool paused;
};

}