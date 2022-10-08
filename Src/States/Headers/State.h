#pragma once

namespace States
{

class IState
{
public:
    virtual ~IState() = default;
    
    virtual bool isDone() = 0;
    virtual void markAsDone() = 0;
    virtual void changeState() = 0;
    virtual void update(float) = 0;
};

class State : public IState
{
public:
    State(){}
    virtual ~State() = default;

    virtual bool isDone(){return done;}
    virtual void markAsDone(){done = true;}
    virtual void changeState(){}
    virtual void update(float){}
private:
    bool done{false};
};

}