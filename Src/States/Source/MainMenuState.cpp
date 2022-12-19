#include <MainMenuState.h>
#include <IniParser.h>
#include <ButtonBuilder.hpp>

namespace States
{

MainMenuState::MainMenuState(
    Core::Config& config,
    std::unique_ptr<Core::MainMenuAssetsManager> assetsManager,
    std::unique_ptr<Gui::MainMenuGuiManager> guiManager)
    : State(
        config,
        std::move(assetsManager),
        std::move(guiManager))
{
    initBackground();
    initFont();
    initKeybinds();
    buttons = State::guiManager->createButtons(font);
}

void MainMenuState::initBackground()
{
    const auto& videoMode = config.graphics.resolution;
    background.setSize(sf::Vector2f(
        static_cast<float>(videoMode.width),
        static_cast<float>(videoMode.height)));
    State::assetsManager->fetchTextureFromFile();
    background.setTexture(&(State::assetsManager->getTexture()));
}

void MainMenuState::initFont()
{
    State::assetsManager->fetchFontFromFile();
    font = State::assetsManager->getFont();
}

void MainMenuState::initKeybinds()
{
    Core::IniParser{}.parseFileTo(
        State::config.keyboard.mainMenuKeys,
        State::config.keyboard.supportedKeys);
}

StateOutput MainMenuState::generateOutput()
{
    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonTexts;

    for(auto& button : this->buttons)
    {
        buttons.push_back(button.second->getBackground());
        buttonTexts.push_back(button.second->getTextContent());
    }
    return StateOutput{background, buttons, buttonTexts};
}

}