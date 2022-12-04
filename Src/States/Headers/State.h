#pragma once

#include <SFML/Graphics.hpp>
#include <Config.h>
#include <AssetsManager.h>
namespace States
{

struct StateOutput
{
    sf::RectangleShape& background;
};

class IState
{
public:
    IState(){}
    virtual ~IState(){}

    virtual std::unique_ptr<IState> getNextState() = 0;
    virtual const StateOutput generateOutput() = 0;

    virtual bool isDone() = 0;
    virtual void markAsDone() = 0;
    virtual void update(float) = 0;
};

class State : public IState
{
public:
    State(
        Core::GraphicsConfig&,
        Core::KeyboardConfig&,
        std::unique_ptr<Core::IAssetsManager>);
    virtual ~State(){}

    virtual std::unique_ptr<IState> getNextState() override {return std::move(nextState);}

    virtual bool isDone() override {return done;}
    virtual void markAsDone() override {done = true;}
    virtual void update(float) override {}
protected:
    bool done{false};
    std::unique_ptr<IState> nextState;
    std::unique_ptr<Core::IAssetsManager> assetsManager;
};

class MainMenuState : public State
{
public:
    MainMenuState(
        Core::GraphicsConfig&,
        Core::KeyboardConfig&,
        std::unique_ptr<Core::IAssetsManager>);
    virtual ~MainMenuState() = default;

    virtual const StateOutput generateOutput() override {return StateOutput{background};}
    const sf::RectangleShape& getBackground() {return background;}
private:
    sf::RectangleShape background;
};

}