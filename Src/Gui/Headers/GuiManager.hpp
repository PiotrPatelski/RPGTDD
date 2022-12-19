#pragma once

#include <SFML/Window.hpp>
#include <ButtonBuilder.hpp>


namespace Gui
{

class IGuiManager
{
public:
    IGuiManager(){}
    virtual ~IGuiManager(){}

    virtual std::map<std::string, std::unique_ptr<IButton>> createButtons(const sf::Font&) = 0;
};

class MainMenuGuiManager : public IGuiManager
{
public:
    MainMenuGuiManager(const sf::VideoMode& screenResolution)
        : buttonBuilder(screenResolution){}
    virtual ~MainMenuGuiManager(){}

    virtual std::map<std::string, std::unique_ptr<IButton>> createButtons(const sf::Font&) override;
private:
    MainMenuButtonBuilder buttonBuilder;
    std::map<std::string, std::unique_ptr<IButton>> buttons;
};



}