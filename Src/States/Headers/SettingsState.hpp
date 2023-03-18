#pragma once

#include <SFML/Graphics.hpp>
#include <MenuState.hpp>
#include <ConfigManager.hpp>
#include <AssetsManager.hpp>
#include <InputListener.hpp>
#include <SettingsGuiManager.hpp>
#include <UserInterface.hpp>

namespace States
{

class SettingsState : public MenuState
{
public:
    SettingsState(
        std::shared_ptr<Core::IConfigManager>,
        std::unique_ptr<FileMgmt::AssetsManager>,
        std::unique_ptr<Gui::GuiManager>,
        std::unique_ptr<Events::InputListener>);
    virtual ~SettingsState() = default;

    virtual void update(const Types::Window& window, const float) override;
    virtual void drawOutput(Types::Window&) override;
    inline std::shared_ptr<sf::RectangleShape> getBackground() const {return background;}
private:
    void initBackground();

    std::shared_ptr<sf::RectangleShape> background;
    std::unique_ptr<Gui::UserInterface> gui;
    std::unique_ptr<Events::InputListener> inputListener;
};

}