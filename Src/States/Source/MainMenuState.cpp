#include <MainMenuState.hpp>
#include <GameState.hpp>
#include <EditorState.hpp>
#include <SettingsState.hpp>
#include <IniParser.hpp>

namespace States
{

MainMenuState::MainMenuState(
    std::shared_ptr<Core::IConfigManager> config,
    std::unique_ptr<FileMgmt::MainMenuAssetsManager> assetsManager,
    std::unique_ptr<Gui::MainMenuGuiManager> guiManager,
    std::unique_ptr<Events::MainMenuInputHandler> inputHandler)
    : State(
        config,
        std::move(assetsManager),
        std::move(guiManager),
        std::move(inputHandler))
{
    initBackground();
    buttons = this->guiManager->createButtons(*(State::assetsManager->getFont()));
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

void MainMenuState::update(const sf::Vector2i& mousePosOnWindow, const float deltaTime)
{
    for(auto& button : buttons)
    {
        button.object->update(mousePosOnWindow);
        nextState = inputHandler->getNextStateOnActiveButton(button);
        if(nextState != nullptr)
            return;
    }
}

void MainMenuState::drawOutput(Core::IWindow& window)
{
    window.draw(*background);
    for(const auto& button : buttons)
    {
        window.draw(button.object->getBackground());
        window.draw(button.object->getTextContent());
    }
}

}