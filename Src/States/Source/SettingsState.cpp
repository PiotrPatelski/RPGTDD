#include <SettingsState.hpp>

namespace States
{

SettingsState::SettingsState(
    std::shared_ptr<Core::IConfigManager> configManager,
    std::unique_ptr<FileMgmt::SettingsAssetsManager> assetsManager,
    std::unique_ptr<Gui::IGuiManager> guiManager,
    std::unique_ptr<Events::IInputListener> inputListener)
    : MenuState(
        configManager,
        std::move(assetsManager)),
    inputListener(std::move(inputListener))
{
    initBackground();
    gui = guiManager->createGui(State::assetsManager->getFont());
}

void SettingsState::initBackground()
{
    const auto& videoMode = configManager->getGraphics().resolution;
    background = std::make_shared<sf::RectangleShape>(
        sf::Vector2f(
            static_cast<float>(videoMode.width),
            static_cast<float>(videoMode.height)));
    background->setTexture(State::assetsManager->getTexture().get());
}

void SettingsState::update(const Core::IWindow& window, const float deltaTime)
{
    gui->update(window.getMousePosition());
    auto action = gui->getActiveAction();
    if(action.has_value())
        get<Events::MenuAction>(action.value())(*this);

    action = inputListener->getActiveAction();
    if(action.has_value())
        get<Events::MenuAction>(action.value())(*this);
}

void SettingsState::drawOutput(Core::IWindow& window)
{
    window.draw(*background);
    gui->drawTo(window);
}

}