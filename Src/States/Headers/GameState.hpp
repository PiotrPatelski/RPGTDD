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

    virtual void update(const Core::IWindow& window, const float) override {}
    virtual void drawOutput(Core::IWindow&) override {}
    virtual void togglePause() override {}
private:
    std::unique_ptr<Gui::UserInterface> gui;
};

}