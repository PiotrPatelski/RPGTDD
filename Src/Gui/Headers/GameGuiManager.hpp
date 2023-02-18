#pragma once

#include <SFML/Window.hpp>
#include <GuiManager.hpp>
#include <ButtonBuilder.hpp>
#include <GameGui.hpp>

namespace Gui
{

class GameGuiManager : public GuiManager
{
public:
    GameGuiManager(std::unique_ptr<ButtonBuilder> buttonBuilder)
        : buttonBuilder(std::move(buttonBuilder)){std::cout<<"GameGuiManager"<<std::endl;}
    virtual ~GameGuiManager(){}

    virtual std::unique_ptr<Gui::UserInterface> createGui(const sf::Font&) override {return std::make_unique<Gui::GameGui>();}
private:
    std::unique_ptr<ButtonBuilder> buttonBuilder;
};

}