//
// MainComponent.h
// By Corey Ford
// 28 March 2020
//

#pragma once

#include <JuceHeader.h>
#include "Person.h"

#define MAX_PEOPLE 25

class MainComponent   : public Component,
                        public Timer
{
public:
    MainComponent();
    ~MainComponent();

    void paint (Graphics&) override;

    void resized() override;
    
    void timerCallback() override;
    
private:
    std::vector<std::unique_ptr<Person>> people;
    const int width = 600;
    const int height = 400;
    Slider densitySlider;
    Label densityLabel;
    Slider velocitySlider;
    Label velocityLabel;
    Slider populationSlider;
    Label populationLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
