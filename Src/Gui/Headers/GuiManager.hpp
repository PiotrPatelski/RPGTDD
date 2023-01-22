#pragma once

#include <SFML/Window.hpp>
#include <ButtonBuilder.hpp>
#include <UserInterface.hpp>


namespace Gui
{

class IGuiManager
{
public:
    IGuiManager(){}
    virtual ~IGuiManager(){}
    
    virtual std::unique_ptr<Gui::IUserInterface> createGui(const std::shared_ptr<sf::Font>) = 0;
};

class MainMenuGuiManager : public IGuiManager
{
public:
    MainMenuGuiManager(std::unique_ptr<IButtonBuilder> buttonBuilder)
        : buttonBuilder(std::move(buttonBuilder)){std::cout<<"MainMenuGuiManager"<<std::endl;}
    virtual ~MainMenuGuiManager(){}

    virtual std::unique_ptr<Gui::IUserInterface> createGui(const std::shared_ptr<sf::Font>) override;
private:
    std::unique_ptr<IButtonBuilder> buttonBuilder;
};

class GameGuiManager : public IGuiManager
{
public:
    GameGuiManager(std::unique_ptr<IButtonBuilder> buttonBuilder)
        : buttonBuilder(std::move(buttonBuilder)){std::cout<<"GameGuiManager"<<std::endl;}
    virtual ~GameGuiManager(){}

    virtual std::unique_ptr<Gui::IUserInterface> createGui(const std::shared_ptr<sf::Font>) override {return std::make_unique<Gui::UserInterface>();}
private:
    std::unique_ptr<IButtonBuilder> buttonBuilder;
};

class EditorGuiManager : public IGuiManager
{
public:
    EditorGuiManager(std::unique_ptr<IButtonBuilder> buttonBuilder)
        : buttonBuilder(std::move(buttonBuilder)){std::cout<<"EditorGuiManager"<<std::endl;}
    virtual ~EditorGuiManager(){}

    virtual std::unique_ptr<Gui::IUserInterface> createGui(const std::shared_ptr<sf::Font>) override {return std::make_unique<Gui::UserInterface>();}
private:
    std::unique_ptr<IButtonBuilder> buttonBuilder;
};

class SettingsGuiManager : public IGuiManager
{
public:
    SettingsGuiManager(std::unique_ptr<IButtonBuilder> buttonBuilder)
        : buttonBuilder(std::move(buttonBuilder)){std::cout<<"SettingsGuiManager"<<std::endl;}
    virtual ~SettingsGuiManager(){}

    virtual std::unique_ptr<Gui::IUserInterface> createGui(const std::shared_ptr<sf::Font>) override;
private:
    std::unique_ptr<IButtonBuilder> buttonBuilder;
};



}