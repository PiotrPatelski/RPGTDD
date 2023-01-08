#pragma once

#include <SFML/Graphics.hpp>
#include <ConfigManager.hpp>
#include <AssetsManager.hpp>
#include <GuiManager.hpp>
#include <InputHandler.hpp>
#include <Button.hpp>
#include <Window.hpp>
namespace States
{

struct StateOutput
{
    std::shared_ptr<sf::RectangleShape> background;
    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonTexts;
};

class IState
{
public:
    IState(){}
    virtual ~IState(){}

    virtual std::unique_ptr<IState> getNextState() = 0;

    virtual const bool isDone() const = 0;
    virtual void markAsDone() = 0;
    virtual void update(const sf::Vector2i&, const float) = 0;
    virtual void drawOutput(Core::IWindow&) = 0;
};

class State : public IState
{
public:
    State(
        std::shared_ptr<Core::IConfigManager>,
        std::unique_ptr<FileMgmt::IAssetsManager>,
        std::unique_ptr<Gui::IGuiManager>,
        std::unique_ptr<Events::IInputHandler>);
    virtual ~State(){}

    virtual std::unique_ptr<IState> getNextState() override {return std::move(nextState);}

    virtual const bool isDone() const override {return done;}
    virtual void markAsDone() override {done = true;}
protected:
    bool done{false};
    std::unique_ptr<IState> nextState;
    std::unique_ptr<FileMgmt::IAssetsManager> assetsManager;
    std::unique_ptr<Gui::IGuiManager> guiManager;
    std::shared_ptr<Core::IConfigManager> config;
    std::unique_ptr<Events::IInputHandler> inputHandler;
};

}