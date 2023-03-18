#pragma once

#include <SFML/System.hpp>

namespace Core
{

class Clock
{
private:
    float deltaTime;
    sf::Clock deltaTimeClock;
public:
    Clock();
    virtual ~Clock(){}

    virtual void updateDeltaTime();
    virtual inline const float getDeltaTime() const {return deltaTime;}
};
    
}