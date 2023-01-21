#pragma once

#include <SFML/Graphics.hpp>
#include <State.hpp>
#include <ConfigManager.hpp>
#include <AssetsManager.hpp>

namespace States
{

class GameState : public State
{
public:
    GameState(
        std::shared_ptr<Core::IConfigManager>,
        std::unique_ptr<FileMgmt::GameAssetsManager>,
        std::unique_ptr<Gui::GameGuiManager>);
    virtual ~GameState() = default;

    virtual void update(const Core::IWindow& window, const float) override {}
    virtual void drawOutput(Core::IWindow&) override {}
private:
    std::unique_ptr<Gui::UserInterface> gui;
};

}