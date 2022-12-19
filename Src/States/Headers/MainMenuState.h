#pragma once

#include <SFML/Graphics.hpp>
#include <State.h>
#include <Config.h>
#include <AssetsManager.h>

namespace States
{

class MainMenuState : public State
{
public:
    MainMenuState(
        Core::Config&,
        std::unique_ptr<Core::MainMenuAssetsManager>,
        std::unique_ptr<Gui::MainMenuGuiManager>);
    virtual ~MainMenuState() = default;

    virtual StateOutput generateOutput() override;
    const sf::RectangleShape getBackground() {return background;}
    const sf::Font getFont() {return font;}
private:
    void initBackground();
    void initFont();
    void initKeybinds();

    sf::RectangleShape background;
    sf::Font font;
    std::map<std::string, std::unique_ptr<Gui::IButton>> buttons;
};

}