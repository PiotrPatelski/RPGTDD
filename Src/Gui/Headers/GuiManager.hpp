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
        : buttonBuilder(screenResolution){std::cout<<"MainMenuGuiManager"<<std::endl;}
    virtual ~MainMenuGuiManager(){}

    virtual std::map<std::string, std::unique_ptr<IButton>> createButtons(const sf::Font&) override;
private:
    MainMenuButtonBuilder buttonBuilder;
    std::map<std::string, std::unique_ptr<IButton>> buttons;
};

class GameGuiManager : public IGuiManager
{
public:
    GameGuiManager(const sf::VideoMode& screenResolution)
        : buttonBuilder(screenResolution){std::cout<<"GameGuiManager"<<std::endl;}
    virtual ~GameGuiManager(){}

    virtual std::map<std::string, std::unique_ptr<IButton>> createButtons(const sf::Font&) override {};
private:
    GameButtonBuilder buttonBuilder;
};

class EditorGuiManager : public IGuiManager
{
public:
    EditorGuiManager(const sf::VideoMode& screenResolution)
        : buttonBuilder(screenResolution){std::cout<<"EditorGuiManager"<<std::endl;}
    virtual ~EditorGuiManager(){}

    virtual std::map<std::string, std::unique_ptr<IButton>> createButtons(const sf::Font&) override {};
private:
    EditorButtonBuilder buttonBuilder;
};

class SettingsGuiManager : public IGuiManager
{
public:
    SettingsGuiManager(const sf::VideoMode& screenResolution)
        : buttonBuilder(screenResolution){std::cout<<"SettingsGuiManager"<<std::endl;}
    virtual ~SettingsGuiManager(){}

    virtual std::map<std::string, std::unique_ptr<IButton>> createButtons(const sf::Font&) override {};
private:
    SettingsButtonBuilder buttonBuilder;
};



}