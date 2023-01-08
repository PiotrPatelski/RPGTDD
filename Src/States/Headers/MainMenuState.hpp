#pragma once

#include <SFML/Graphics.hpp>
#include <State.hpp>

namespace States
{

class MainMenuState : public State
{
public:
    MainMenuState(
        std::shared_ptr<Core::IConfigManager>,
        std::unique_ptr<FileMgmt::MainMenuAssetsManager>,
        std::unique_ptr<Gui::MainMenuGuiManager>,
        std::unique_ptr<Events::MainMenuInputHandler>);
    virtual ~MainMenuState() = default;

    virtual const bool isDone() const override {return inputHandler->isStateReadyToChange();}

    virtual void update(const sf::Vector2i&, const float) override;
    virtual void drawOutput(Core::IWindow&) override;
    inline std::shared_ptr<sf::RectangleShape> getBackground() const {return background;}
    inline std::shared_ptr<sf::Font> getFont() const {return font;}
private:
    void initBackground();
    void initFont();

    std::shared_ptr<sf::RectangleShape> background;
    std::shared_ptr<sf::Font> font;
    std::vector<std::unique_ptr<Gui::IButton>> buttons;
};

}