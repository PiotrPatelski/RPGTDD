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
        std::unique_ptr<Core::MainMenuAssetsManager>);
    virtual ~MainMenuState() = default;

    virtual const StateOutput generateOutput() override {return StateOutput{background};}
    const sf::RectangleShape& getBackground() {return background;}
    const sf::Font& getFont() {return font;}
private:
    void initBackground();
    void initFont();
    void initKeybinds();

    sf::RectangleShape background;
    sf::Font font;
};

}