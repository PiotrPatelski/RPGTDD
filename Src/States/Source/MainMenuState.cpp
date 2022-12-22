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
    buttons = State::guiManager->createButtons(*font);
}

void MainMenuState::initBackground()
{
    const auto& videoMode = config.graphics.resolution;
    background = std::make_shared<sf::RectangleShape>(
        sf::Vector2f(
            static_cast<float>(videoMode.width),
            static_cast<float>(videoMode.height)));
    background->setTexture(State::assetsManager->getTexture().get());
}

void MainMenuState::initFont()
{
    font = State::assetsManager->getFont();
}

void MainMenuState::initKeybinds()
{
    State::config.keyboard.mainMenuKeys = Core::IniParser{}.
        parseMainMenuKeys(State::config.keyboard.supportedKeys);
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