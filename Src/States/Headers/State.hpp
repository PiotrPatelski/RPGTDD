#pragma once

#include <ConfigManager.hpp>
#include <AssetsManager.hpp>

namespace Types
{
class Window;
}
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
    virtual std::shared_ptr<FileMgmt::IConfigManager> getConfig() = 0;

    virtual void update(const Types::Window&, const float) = 0;
    virtual void drawOutput(Types::Window&) = 0;
};

class State : public IState
{
public:
    State(
        std::shared_ptr<FileMgmt::IConfigManager>,
        std::unique_ptr<FileMgmt::AssetsManager>);
    virtual ~State(){}

    virtual void finishState() override {readyToChange = true;}
    virtual void setNextState (std::unique_ptr<IState> nextState) override {this->nextState = std::move(nextState);}

    virtual const bool isReadyToChange() const override {return readyToChange;}
    virtual std::unique_ptr<IState> getNextState() override {return std::move(nextState);}
    virtual std::shared_ptr<FileMgmt::IConfigManager> getConfig() override {return configManager;}
protected:
    bool readyToChange{false};
    std::unique_ptr<IState> nextState;
    std::unique_ptr<FileMgmt::AssetsManager> assetsManager;
    std::shared_ptr<FileMgmt::IConfigManager> configManager;
};

}