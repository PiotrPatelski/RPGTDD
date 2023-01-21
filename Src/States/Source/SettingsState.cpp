#include <SettingsState.hpp>

namespace States
{

SettingsState::SettingsState(
    std::shared_ptr<Core::IConfigManager> config,
    std::unique_ptr<FileMgmt::SettingsAssetsManager> assetsManager,
    std::unique_ptr<Gui::SettingsGuiManager> guiManager)
    : State(
        config,
        std::move(assetsManager))
{
    initBackground();
    gui = guiManager->createGui(State::assetsManager->getFont());
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

void SettingsState::update(const Core::IWindow&, const float)
{}

void SettingsState::drawOutput(Core::IWindow& window)
{
    window.draw(*background);
    gui->drawTo(window);
}

}