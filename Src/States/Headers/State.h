#pragma once
namespace States
{

class IState
{
public:
    IState(){}
    virtual ~IState(){}

    virtual std::unique_ptr<IState> getNextState() = 0;
    
    virtual bool isDone() = 0;
    virtual void markAsDone() = 0;
    virtual void update(float) = 0;
};

class State : public IState
{
public:
    State();
    virtual ~State(){}

    virtual std::unique_ptr<IState> getNextState() override {return std::move(nextState);}

    virtual bool isDone(){return done;}
    virtual void markAsDone(){done = true;}
    virtual void update(float){}
protected:
    bool done{false};
    std::unique_ptr<IState> nextState;
};

class MainMenuState : public State
{
public:
    MainMenuState();
    virtual ~MainMenuState() = default;

private:

};

}