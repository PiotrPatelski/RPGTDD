#pragma once

#include <SFML/Window.hpp>
#include <ButtonBuilder.hpp>
#include <ButtonListBuilder.hpp>
#include <UserInterface.hpp>


namespace Gui
{

class IGuiManager
{
public:
    IGuiManager(){}
    virtual ~IGuiManager(){}
    
    virtual std::unique_ptr<Gui::UserInterface> createGui(const std::shared_ptr<sf::Font>) = 0;
};

class MainMenuGuiManager : public IGuiManager
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
    std::unique_ptr<Gui::UserInterface> gui;
};

class GameGuiManager : public IGuiManager
{
public:
    GameGuiManager(std::unique_ptr<IButtonBuilder> buttonBuilder)
        : buttonBuilder(std::move(buttonBuilder)){std::cout<<"GameGuiManager"<<std::endl;}
    virtual ~GameGuiManager(){}

    virtual std::unique_ptr<Gui::UserInterface> createGui(const std::shared_ptr<sf::Font>) override {return std::make_unique<Gui::MenuGui>();}
private:
    std::unique_ptr<IButtonBuilder> buttonBuilder;
};

class EditorGuiManager : public IGuiManager
{
public:
    EditorGuiManager(std::unique_ptr<IButtonBuilder> buttonBuilder)
        : buttonBuilder(std::move(buttonBuilder)){std::cout<<"EditorGuiManager"<<std::endl;}
    virtual ~EditorGuiManager(){}

    virtual std::unique_ptr<Gui::UserInterface> createGui(const std::shared_ptr<sf::Font>) override {return std::make_unique<Gui::MenuGui>();}
private:
    std::unique_ptr<IButtonBuilder> buttonBuilder;
};

class SettingsGuiManager : public IGuiManager
{
public:
    SettingsGuiManager(
        std::unique_ptr<IButtonBuilder> buttonBuilder,
        std::unique_ptr<ButtonListBuilder> dropDownListBuilder)
        : buttonBuilder(std::move(buttonBuilder)),
          dropDownListBuilder(std::move(dropDownListBuilder))
        {std::cout<<"SettingsGuiManager"<<std::endl;}
    virtual ~SettingsGuiManager(){}

    virtual std::unique_ptr<Gui::UserInterface> createGui(const std::shared_ptr<sf::Font>) override;
private:
    void addApplyButton(const std::shared_ptr<sf::Font>);
    void addBackButton(const std::shared_ptr<sf::Font>);
    void addResolutionList(const std::shared_ptr<sf::Font>);
    void fillListWithResolutionModes(ButtonList&);
    std::unique_ptr<IButtonBuilder> buttonBuilder;
    std::unique_ptr<ButtonListBuilder> dropDownListBuilder;
    std::unique_ptr<Gui::UserInterface> gui;
};


}