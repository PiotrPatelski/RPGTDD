#pragma once

#include <SFML/Graphics.hpp>
#include <MapState.hpp>
#include <ConfigManager.hpp>
#include <GameAssetsManager.hpp>
#include <GameGuiManager.hpp>
#include <UserInterface.hpp>

namespace States
{

class GameState : public MapState
{
public:
    GameState(
        std::shared_ptr<Core::IConfigManager>,
        std::unique_ptr<FileMgmt::AssetsManager>,
        std::unique_ptr<Gui::GuiManager>);
    virtual ~GameState() = default;

    virtual void update(const Types::IWindow& window, const float) override {}
    virtual void drawOutput(Types::IWindow&) override {}
    virtual void togglePause() override {}
    virtual void addTileAt(const sf::Vector2i&) override {}
    virtual void removeTileAt(const sf::Vector2i&) override {}
private:
    std::unique_ptr<Gui::UserInterface> gui;
};

}