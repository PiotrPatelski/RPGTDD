#pragma once

#include <SFML/Graphics.hpp>
#include <MenuState.hpp>
#include <MainMenuGuiManager.hpp>
#include <MainMenuAssetsManager.hpp>
#include <UserInterface.hpp>

namespace States
{

class MainMenuState : public MenuState
{
public:
    MainMenuState(
        std::shared_ptr<Core::IConfigManager>,
        std::unique_ptr<FileMgmt::AssetsManager>,
        std::unique_ptr<Gui::GuiManager>);
    virtual ~MainMenuState() = default;

    virtual void update(const Types::IWindow& window, const float) override;
    virtual void drawOutput(Types::IWindow&) override;
    inline std::shared_ptr<sf::RectangleShape> getBackground() const {return background;}
private:
    void initBackground();

    std::shared_ptr<sf::RectangleShape> background;
    std::unique_ptr<Gui::UserInterface> gui;
};

}