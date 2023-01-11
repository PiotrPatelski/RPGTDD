#include <SettingsState.hpp>

namespace States
{

SettingsState::SettingsState(
    std::shared_ptr<Core::IConfigManager> config,
    std::unique_ptr<FileMgmt::SettingsAssetsManager> assetsManager,
    std::unique_ptr<Gui::SettingsGuiManager> guiManager,
    std::unique_ptr<Events::SettingsInputHandler> inputHandler)
    : State(
        config,
        std::move(assetsManager),
        std::move(guiManager),
        std::move(inputHandler))
{
    initBackground();
    buttons = this->guiManager->createButtons(*(State::assetsManager->getFont()));
}

void SettingsState::initBackground()
{
    const auto& videoMode = config->getGraphics().resolution;
    background = std::make_shared<sf::RectangleShape>(
        sf::Vector2f(
            static_cast<float>(videoMode.width),
            static_cast<float>(videoMode.height)));
    background->setTexture(State::assetsManager->getTexture().get());
}

void SettingsState::update(const sf::Vector2i&, const float)
{}

void SettingsState::drawOutput(Core::IWindow& window)
{
    window.draw(*background);
    for(const auto& button : buttons)
    {
        window.draw(button.object->getBackground());
        window.draw(button.object->getTextContent());
    }
}

}