//
// Person.cpp
// By Corey Ford
// 28 March 2020
//

#include "Person.h"

Person::Person (int startX, int startY) : x(startX), y(startY)
{
    velX = velY = 1;
    internalClock = 0;
    
    if (Random::getSystemRandom().nextInt (10) == 1)
        becomeInfected();
    else
        state = healthy;
    
    setSize (10, 10);
}

Person::~Person(){}

void Person::paint (Graphics& g)
{
    if(state == healthy) g.setColour(Colours::green);
    if(state == infected) g.setColour(Colours::red);
    
    g.fillEllipse(getLocalBounds().toFloat());
}

void Person::resized(){}

int Person::updateAndGetX()
{
    x = x+velX;
    return x;
}

int Person::updateAndGetY()
{
    y = y+velY;
    return y;
}

void Person::setVelocity (int newVel, bool isX)
{
    if(isX)
        velX = newVel;
    else
        velY = newVel;
}

void Person::invertVelocity (bool isX)
{
    if(isX)
        velX = -velX;
    else
        velY = -velY;
}

void Person::becomeInfected()
{
    invertVelocity (true);
    invertVelocity (false);
    
    state = infected;
    internalClock = 100;
    
    for (int i = 0; i < 20; ++i) //just pull them apart!
        updateAndGetY();
}

void Person::checkHealth()
{
    if (internalClock != 0)
        internalClock -= 1;
    else
        state = healthy;
    
    repaint();
}

Person::State Person::getState()
{
    return state;
}

void Person::mouseDown (const MouseEvent& event)
{
    becomeInfected();
}
