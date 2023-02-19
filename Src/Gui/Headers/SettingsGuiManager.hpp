#pragma once

#include <SFML/Window.hpp>
#include <GuiManager.hpp>
namespace Gui
{

class Button;
class ButtonBuilder;
class ButtonListBuilder;
class UserInterface;

class SettingsGuiManager : public GuiManager
{
public:
    SettingsGuiManager(
        const sf::VideoMode&,
        std::unique_ptr<ButtonBuilder>,
        std::unique_ptr<ButtonListBuilder>);
    virtual ~SettingsGuiManager(){}

    virtual std::unique_ptr<Gui::UserInterface> createGui(const sf::Font&) override;
private:
    void addApplyButton(const sf::Font&);
    void addBackButton(const sf::Font&);
    void addResolutionList(const sf::Font&);
    void fillListWithResolutionModes(ButtonListBuilder&, const sf::Font&);
    std::unique_ptr<Button> createTriggerButton(const VectorMath::ScreenPercentagePoint&, const sf::Font&);
    std::unique_ptr<ButtonBuilder> buttonBuilder;
    std::unique_ptr<ButtonListBuilder> dropDownListBuilder;
    std::unique_ptr<Gui::UserInterface> gui;
    sf::VideoMode resolution;
};

}