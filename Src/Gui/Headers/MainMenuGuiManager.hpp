#pragma once

#include <SFML/Window.hpp>
#include <GuiManager.hpp>
#include <ButtonBuilder.hpp>
#include <ButtonListBuilder.hpp>

namespace Gui
{

class UserInterface;

class MainMenuGuiManager : public GuiManager
{
public:
    MainMenuGuiManager(const sf::VideoMode& resolution, std::unique_ptr<ButtonBuilder> buttonBuilder)
        : buttonBuilder(std::move(buttonBuilder)),
          resolution(resolution){std::cout<<"MainMenuGuiManager"<<std::endl;}
    virtual ~MainMenuGuiManager(){}

    virtual std::unique_ptr<Gui::UserInterface> createGui(const sf::Font&) override;
private:
    void addToGameButton(const sf::Font&);
    void addToSettingsButton(const sf::Font&);
    void addToEditorButton(const sf::Font&);
    void addExitButton(const sf::Font&);
    std::unique_ptr<ButtonBuilder> buttonBuilder;
    std::unique_ptr<UserInterface> gui;
    sf::VideoMode resolution;
};

}