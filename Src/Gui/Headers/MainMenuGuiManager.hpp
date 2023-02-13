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
    MainMenuGuiManager(std::unique_ptr<IButtonBuilder> buttonBuilder)
        : buttonBuilder(std::move(buttonBuilder)){std::cout<<"MainMenuGuiManager"<<std::endl;}
    virtual ~MainMenuGuiManager(){}

    virtual std::unique_ptr<Gui::UserInterface> createGui(const std::shared_ptr<sf::Font>) override;
private:
    void addToGameButton(const std::shared_ptr<sf::Font>);
    void addToSettingsButton(const std::shared_ptr<sf::Font>);
    void addToEditorButton(const std::shared_ptr<sf::Font>);
    void addExitButton(const std::shared_ptr<sf::Font>);
    std::unique_ptr<IButtonBuilder> buttonBuilder;
    std::unique_ptr<UserInterface> gui;
};

}