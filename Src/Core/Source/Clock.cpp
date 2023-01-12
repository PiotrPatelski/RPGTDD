#include <Clock.hpp>


namespace Core
{

Clock::Clock()
: deltaTime{0.f}
{

}

void Clock::updateDeltaTime()
{
    /*Updates dt with the time it takes to update and render one frame*/
    deltaTime = deltaTimeClock.restart().asSeconds();
}
}
