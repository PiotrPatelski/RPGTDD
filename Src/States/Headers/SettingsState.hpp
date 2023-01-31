#pragma once

#include <SFML/Graphics.hpp>
#include <MenuState.hpp>
#include <ConfigManager.hpp>
#include <AssetsManager.hpp>
#include <InputListener.hpp>
#include <GuiManager.hpp>
#include <UserInterface.hpp>

namespace States
{

class SettingsState : public MenuState
{
public:
    SettingsState(
        std::shared_ptr<Core::IConfigManager>,
        std::unique_ptr<FileMgmt::SettingsAssetsManager>,
        std::unique_ptr<Gui::IGuiManager>,
        std::unique_ptr<Events::IInputListener>);
    virtual ~SettingsState() = default;

    virtual void update(const Core::IWindow& window, const float) override;
    virtual void drawOutput(Core::IWindow&) override;
    inline std::shared_ptr<sf::RectangleShape> getBackground() const {return background;}
private:
    void initBackground();

    std::shared_ptr<sf::RectangleShape> background;
    std::unique_ptr<Gui::UserInterface> gui;
    std::unique_ptr<Events::IInputListener> inputListener;
};

}