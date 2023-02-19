#include <SettingsGuiManager.hpp>
#include <MenuGui.hpp>
#include <State.hpp>
#include <ButtonBuilder.hpp>
#include <ButtonListBuilder.hpp>
#include <UserInterface.hpp>
#include <ButtonTextCalculations.hpp>

namespace Gui
{

SettingsGuiManager::SettingsGuiManager(
    const sf::VideoMode& resolution,
    std::unique_ptr<ButtonBuilder> buttonBuilder,
    std::unique_ptr<ButtonListBuilder> dropDownListBuilder)
    : buttonBuilder(std::move(buttonBuilder)),
        dropDownListBuilder(std::move(dropDownListBuilder)),
        resolution(resolution)
{
    std::cout<<"SettingsGuiManager"<<std::endl;
}

std::unique_ptr<Gui::UserInterface> SettingsGuiManager::createGui(const sf::Font& font)
{
    gui = std::make_unique<Gui::MenuGui>();
    std::cout<<"SettingsGuiManager::createGui"<<std::endl;
    addApplyButton(font);
    addBackButton(font);
    addResolutionList(font);
    std::cout<<"SettingsGuiManager::createGui done"<<std::endl;
    return std::move(gui);
}

void SettingsGuiManager::addApplyButton(const sf::Font& font)
{
    gui->addButton(buttonBuilder->
            withTextContent(sf::Text("Apply", font)).
            atPosition(VectorMath::ScreenPercentagePoint(resolution, sf::Vector2f(72.f, 81.f))).
            withSize(VectorMath::ScreenPercentagePoint(resolution, sf::Vector2f(13.f, 6.f))).
            build(),
        Events::ApplySettings());
}

void SettingsGuiManager::addBackButton(const sf::Font& font)
{
    gui->addButton(buttonBuilder->
            withTextContent(sf::Text("Back", font)).
            atPosition(VectorMath::ScreenPercentagePoint(resolution, sf::Vector2f(55.f, 81.f))).
            withSize(VectorMath::ScreenPercentagePoint(resolution, sf::Vector2f(13.f, 6.f))).
            build(),
        Events::ToMainMenuState());
}

void SettingsGuiManager::addResolutionList(const sf::Font& font)
{
    const VectorMath::ScreenPercentagePoint size{resolution, sf::Vector2f(10.4f, 4.5f)};
    const sf::Text listName{"Resolution", font, VectorMath::calculateFontSize(size.toPixels())};

    dropDownListBuilder->
        withTriggerButton(createTriggerButton(size, font)).
        withTextContent(listName);

    fillListWithResolutionModes(*dropDownListBuilder, font);

    gui->addButtonList(dropDownListBuilder->build());
}

void SettingsGuiManager::fillListWithResolutionModes(ButtonListBuilder& listBuilder, const sf::Font& font)
{
    auto availableModes = sf::VideoMode::getFullscreenModes();
    for(auto mode : availableModes)
    {
        auto sectionName = std::to_string(mode.width) + 'x' + std::to_string(mode.height);
        listBuilder.withSection(sf::Text(sectionName, font), Events::SetResolutionTo(mode));
    }
}

std::unique_ptr<Button> SettingsGuiManager::createTriggerButton(const VectorMath::ScreenPercentagePoint& size, const sf::Font& font)
{
    const auto triggerButtonName = std::to_string(resolution.width) + 'x' + std::to_string(resolution.height);
    const sf::Text triggerButtonText{triggerButtonName, font, VectorMath::calculateFontSize(size.toPixels())};

    return buttonBuilder->
        withTextContent(triggerButtonText).
        atPosition(VectorMath::ScreenPercentagePoint(resolution, sf::Vector2f(42.f, 42.f))).
        withSize(size).
        build();
}

}