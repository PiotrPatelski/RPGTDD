#include <State.h>

namespace States
{

State::State(
    Core::GraphicsConfig& gfxConfig,
    Core::KeyboardConfig& kbrdConfig,
    std::unique_ptr<Core::IAssetsManager> assetsManager)
    : assetsManager(std::move(assetsManager))
{

}

MainMenuState::MainMenuState(
    Core::GraphicsConfig& gfxConfig,
    Core::KeyboardConfig& kbrdConfig,
    std::unique_ptr<Core::IAssetsManager> assetsManager)
    : State(gfxConfig, kbrdConfig, std::move(assetsManager))
{
    const auto& videoMode = gfxConfig.resolution;
    background.setSize(sf::Vector2f(
        static_cast<float>(videoMode.width),
        static_cast<float>(videoMode.height)));
    State::assetsManager->fetchTextureFromFile();
    background.setTexture(&(State::assetsManager->getTexture()));
}

}