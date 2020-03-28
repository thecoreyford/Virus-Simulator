//
// Person.hpp
// By Corey Ford
// 28 March 2020
//

#pragma once

#include <JuceHeader.h>


class Person  : public Component
{
public:
    Person (int startX, int startY);
    
    ~Person() override;

    enum State
    {
        infected,
        healthy
    };

    void paint (Graphics& g) override;
    
    void resized() override;
    
    int updateAndGetX();
    
    int updateAndGetY();
    
    void setVelocity(int newVel, bool isX);
    
    void invertVelocity(bool isX);
    
    void becomeInfected();
    
    void checkHealth();
    
    State getState();
    
    void mouseDown (const MouseEvent& event) override;
    
private:
    State state;
    
    double x, y, velX, velY;
    
    int internalClock;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Person)
};
