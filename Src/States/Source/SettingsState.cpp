#include <SettingsState.hpp>

namespace States
{

SettingsState::SettingsState(
    std::shared_ptr<Core::IConfigManager> configManager,
    std::unique_ptr<FileMgmt::AssetsManager> assetsManager,
    std::unique_ptr<Gui::GuiManager> guiManager,
    std::unique_ptr<Events::InputListener> inputListener)
    : MenuState(
        configManager,
        std::move(assetsManager)),
    inputListener(std::move(inputListener))
{
    initBackground();
    gui = guiManager->createGui(State::assetsManager->getFont("MENU_BUTTON"));
}

void SettingsState::initBackground()
{
    const auto& videoMode = configManager->getGraphics().resolution;
    background = std::make_shared<sf::RectangleShape>(
        sf::Vector2f(
            static_cast<float>(videoMode.width),
            static_cast<float>(videoMode.height)));
    background->setTexture(State::assetsManager->getTexture("MENU_BACKGROUND"));
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