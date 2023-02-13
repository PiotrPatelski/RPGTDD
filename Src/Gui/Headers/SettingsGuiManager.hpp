#pragma once

#include <SFML/Window.hpp>
#include <GuiManager.hpp>
#include <ButtonBuilder.hpp>
#include <ButtonListBuilder.hpp>
#include <UserInterface.hpp>

namespace Gui
{

class UserInterface;

class SettingsGuiManager : public GuiManager
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