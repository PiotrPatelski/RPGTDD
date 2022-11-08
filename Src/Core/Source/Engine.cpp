#include <Engine.h>

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
GraphicsConfig& Engine::getGraphicsConfig()
{
    return graphicsConfig;
}
KeyboardConfig& Engine::getKeyboardConfig()
{
    return keyboardConfig;
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
    window->display();
}

void Engine::launchWindow()
{
    window->openWithSettings(graphicsConfig);
}

void Engine::runInitialState()
{
    stateMachine->runState(std::make_unique<States::MainMenuState>());
}

}