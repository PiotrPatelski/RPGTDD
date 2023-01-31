#pragma once

#include <ConfigManager.hpp>
#include <AssetsManager.hpp>
#include <Window.hpp>
namespace States
{

class IState
{
public:
    IState(){}
    virtual ~IState(){}

    virtual void finishState() = 0;
    virtual void setNextState (std::unique_ptr<IState>) = 0;

    virtual const bool isReadyToChange() const = 0;
    virtual std::unique_ptr<IState> getNextState() = 0;
    virtual std::shared_ptr<Core::IConfigManager> getConfig() = 0;

    virtual void update(const Core::IWindow&, const float) = 0;
    virtual void drawOutput(Core::IWindow&) = 0;
};

class State : public IState
{
public:
    State(
        std::shared_ptr<Core::IConfigManager>,
        std::unique_ptr<FileMgmt::IAssetsManager>);
    virtual ~State(){}

    virtual void finishState() override {readyToChange = true;}
    virtual void setNextState (std::unique_ptr<IState> nextState) override {this->nextState = std::move(nextState);}

    virtual const bool isReadyToChange() const override {return readyToChange;}
    virtual std::unique_ptr<IState> getNextState() override {return std::move(nextState);}
    virtual std::shared_ptr<Core::IConfigManager> getConfig() override {return configManager;}
protected:
    bool readyToChange{false};
    std::unique_ptr<IState> nextState;
    std::unique_ptr<FileMgmt::IAssetsManager> assetsManager;
    std::shared_ptr<Core::IConfigManager> configManager;
};

}