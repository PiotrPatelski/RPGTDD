#include <Clock.h>


namespace Core
{

Clock::Clock()
: deltaTime{0.f}
{

}

void Clock::updateDeltaTime()
{
    deltaTime = deltaTimeClock.restart().asSeconds();
}
}
