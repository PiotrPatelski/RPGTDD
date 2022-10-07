#pragma once


namespace Core
{

class IStateMachine
{
public:
    IStateMachine(){}
    virtual ~IStateMachine(){}

    virtual bool isWorkDone() = 0;
    virtual void update(bool, float) = 0;
};

class StateMachine : public IStateMachine
{
public:
    StateMachine(){}
    virtual ~StateMachine(){}

    virtual bool isWorkDone(){return false;};
    virtual void update(bool, float) override {};
private:

};

}