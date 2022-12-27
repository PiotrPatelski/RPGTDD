#include <MainMenuState.h>
#include <IniParser.h>
#include <ButtonBuilder.hpp>

namespace States
{

MainMenuState::MainMenuState(
    std::shared_ptr<Core::ConfigManager> config,
    std::unique_ptr<Core::MainMenuAssetsManager> assetsManager,
    std::unique_ptr<Gui::MainMenuGuiManager> guiManager)
    : State(
        config,
        std::move(assetsManager),
        std::move(guiManager))
{
    initBackground();
    initFont();
    buttons = State::guiManager->createButtons(*font);
}

void MainMenuState::initBackground()
{
    const auto& videoMode = config->getGraphics().resolution;
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