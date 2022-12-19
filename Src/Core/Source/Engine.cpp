#include <Engine.h>
#include <GuiManager.hpp>

namespace Core
{

Engine::Engine(const ICoreBuilder& builder)
: 
window(builder.createWindow()),
clock(builder.createClock()),
stateMachine(builder.createStateMachine())
{}

void Engine::updateDeltaTime()
{
    clock->updateDeltaTime();
}

Config& Engine::getConfig()
{
    return config;
}

bool Engine::isWindowOpen()
{ 
    return window->isActive();
}

bool Engine::updateState()
{
    window->handleSfmlEvents(sfmlEvent);
    if(not stateMachine->isNoStateActive())
    {
        stateMachine->update(window->isCurrentlyFocused(), clock->getDeltaTime());
        return true;
    }
    return false;
}

void Engine::closeWindow()
{
    window->close();

}

void Engine::displayRenderedFrame()
{    
    window->clear();
    if(not stateMachine->isNoStateActive())
        window->drawStateOutput(stateMachine->getOutput());
    window->display();
}

void Engine::launchWindow()
{
    window->openWithSettings(config.graphics);
}

void Engine::runInitialState()
{
    stateMachine->runState(std::make_unique<States::MainMenuState>(
        config,
        std::make_unique<MainMenuAssetsManager>(),
        std::make_unique<Gui::MainMenuGuiManager>(config.graphics.resolution)
    ));
}

}