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
        std::unique_ptr<ButtonBuilder> buttonBuilder,
        std::unique_ptr<ButtonListBuilder> dropDownListBuilder)
        : buttonBuilder(std::move(buttonBuilder)),
          dropDownListBuilder(std::move(dropDownListBuilder))
        {std::cout<<"SettingsGuiManager"<<std::endl;}
    virtual ~SettingsGuiManager(){}

    virtual std::unique_ptr<Gui::UserInterface> createGui(const sf::Font&) override;
private:
    void addApplyButton(const sf::Font&);
    void addBackButton(const sf::Font&);
    void addResolutionList(const sf::Font&);
    void fillListWithResolutionModes(ButtonList&, const sf::Font&);
    std::unique_ptr<ButtonBuilder> buttonBuilder;
    std::unique_ptr<ButtonListBuilder> dropDownListBuilder;
    std::unique_ptr<Gui::UserInterface> gui;
};

}