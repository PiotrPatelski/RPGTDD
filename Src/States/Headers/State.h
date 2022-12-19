#pragma once

#include <SFML/Graphics.hpp>
#include <Config.h>
#include <AssetsManager.h>
#include <GuiManager.hpp>
#include <Button.hpp>
namespace States
{

struct StateOutput
{
    sf::RectangleShape background;
    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonTexts;
};

class IState
{
public:
    IState(){}
    virtual ~IState(){}

    virtual std::unique_ptr<IState> getNextState() = 0;
    virtual StateOutput generateOutput() = 0;

    virtual bool isDone() = 0;
    virtual void markAsDone() = 0;
    virtual void update(float) = 0;
};

class State : public IState
{
public:
    State(
        Core::Config&,
        std::unique_ptr<Core::IAssetsManager>,
        std::unique_ptr<Gui::IGuiManager>);
    virtual ~State(){}

    virtual std::unique_ptr<IState> getNextState() override {return std::move(nextState);}

    virtual bool isDone() override {return done;}
    virtual void markAsDone() override {done = true;}
    virtual void update(float) override {}
protected:
    bool done{false};
    std::unique_ptr<IState> nextState;
    std::unique_ptr<Core::IAssetsManager> assetsManager;
    std::unique_ptr<Gui::IGuiManager> guiManager;
    Core::Config& config;
};

}