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
    virtual const float getDeltaTime() const = 0;
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
    virtual inline const float getDeltaTime() const override {return deltaTime;}
};
    
}