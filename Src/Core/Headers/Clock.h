#pragma once

#include <SFML/System.hpp>

namespace Core
{

class IClock
{
public:
    IClock(){}
    virtual ~IClock(){}

    virtual void updateDeltaTime() = 0;
    virtual float getDeltaTime() = 0;
};

class Clock : public IClock
{
private:
    float deltaTime;
    sf::Clock deltaTimeClock;
public:
    Clock();
    virtual ~Clock(){}

    virtual void updateDeltaTime() override;
    virtual float getDeltaTime() override {return deltaTime;}
};
    
}