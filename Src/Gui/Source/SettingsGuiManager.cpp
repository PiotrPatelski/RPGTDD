#include <SettingsGuiManager.hpp>
#include <MenuGui.hpp>
#include <State.hpp>

namespace Gui
{

std::unique_ptr<Gui::UserInterface> SettingsGuiManager::createGui(const std::shared_ptr<sf::Font> font)
{
    gui = std::make_unique<Gui::MenuGui>();
    std::cout<<"SettingsGuiManager::createGui"<<std::endl;
    addApplyButton(font);
    addBackButton(font);
    addResolutionList(font);
    std::cout<<"SettingsGuiManager::createGui done"<<std::endl;
    return std::move(gui);
}

void SettingsGuiManager::addApplyButton(const std::shared_ptr<sf::Font> font)
{
    gui->addButton(buttonBuilder->
            withTextContent("Apply").withFont(font).
            atPosition(72.f, 81.f).withSize(13.f, 6.f).
            build(),
        Events::ApplySettings());
}

void SettingsGuiManager::addBackButton(const std::shared_ptr<sf::Font> font)
{
    gui->addButton(buttonBuilder->
            withTextContent("Back").withFont(font).
            atPosition(55.f, 81.f).withSize(13.f, 6.f).
            build(),
        Events::ToMainMenuState());
}

void SettingsGuiManager::addResolutionList(const std::shared_ptr<sf::Font> font)
{
    auto resolutionList = dropDownListBuilder->
        withTextContent(sf::Text("Resolution", *font)).
        build(buttonBuilder->
            withTextContent("").withFont(font).
            atPosition(42.f, 42.f).withSize(10.4f, 4.5f).
            build());

    fillListWithResolutionModes(*resolutionList);

    gui->addButtonList(std::move(resolutionList));
}

void SettingsGuiManager::fillListWithResolutionModes(ButtonList& list)
{
    auto availableModes = sf::VideoMode::getFullscreenModes();
    for(auto mode : availableModes)
    {
        auto sectionName = std::to_string(mode.width) + 'x' + std::to_string(mode.height);
        list.addSection(sectionName, Events::SetResolutionTo(mode));
    }
}

}