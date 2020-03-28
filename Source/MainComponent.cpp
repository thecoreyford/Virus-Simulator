//
// MainComponent.cpp
// By Corey Ford
// 28 March 2020
//

#include "MainComponent.h"

MainComponent::MainComponent()
{
    setSize (width, height + 150);
    
    densitySlider.setRange (5, 20, 1);
    densitySlider.setValue (10);
    addAndMakeVisible (densitySlider);
    
    startTimer (120);
    
    for (int i = 0; i < MAX_PEOPLE; ++i)
    {
        people.push_back (std::make_unique<Person> (Random::getSystemRandom().nextInt (width),
                                                    Random::getSystemRandom().nextInt (height)));
        addAndMakeVisible (*people.back());
    }

    //---
    
    velocitySlider.setRange (1.0, 5.0);
    addAndMakeVisible (velocitySlider);
    velocitySlider.onValueChange = [this]
    {
         for (int i = 0; i < people.size(); ++i)
         {
             if (Random::getSystemRandom().nextInt (1) == 0){
                 people[i]->setVelocity (-velocitySlider.getValue(), true);
                 people[i]->setVelocity (velocitySlider.getValue(), false);
             } else {
                 people[i]->setVelocity (velocitySlider.getValue(), true);
                 people[i]->setVelocity (-velocitySlider.getValue(), false);
             }
         }
    };
    
    populationSlider.setRange (1.0, MAX_PEOPLE, 1.0);
    populationSlider.setValue (8);
    addAndMakeVisible (populationSlider);
    populationSlider.onValueChange = [this]
    {
        for (int i = 0; i < MAX_PEOPLE; ++i)
        {
            if (i < populationSlider.getValue())
                people[i]->setVisible (true);
            else
                people[i]->setVisible (false);
        }
    };
    
    //---
    
    addAndMakeVisible(densityLabel);
    densityLabel.setText ("Density", dontSendNotification);
    densityLabel.attachToComponent (&densitySlider, true);
    
    addAndMakeVisible (velocityLabel);
    velocityLabel.setText ("Distance", dontSendNotification);
    velocityLabel.attachToComponent (&velocitySlider, true);
    
    addAndMakeVisible (populationLabel);
    populationLabel.setText ("Population", dontSendNotification);
    populationLabel.attachToComponent (&populationSlider, true);
}

MainComponent::~MainComponent()
{
    stopTimer();
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    for (auto& p : people)
    {
        int x = p->updateAndGetX();
        int y = p->updateAndGetY();
        
        if (x < 0 || x > width){
            p->invertVelocity(true);
        }
        if (y < 0 || y > height){
            p->invertVelocity(false);
        }
        
        p->setBounds (x, y, densitySlider.getValue(), densitySlider.getValue());
    }
    
    densitySlider.setBounds (80, height, width - 80, 50);
    velocitySlider.setBounds (80, height + 50, width - 80, 50);
    populationSlider.setBounds (80, height + 100, width - 80, 50);
}

void MainComponent::timerCallback()
{
    for (int i = 0; i < people.size(); ++i)
    {
        //move the dude
        resized();
        
        /*____________________________________________________________________*/
        // check collisions
        if (people[i]->getState() == Person::infected)
        {
            for (auto& p : people)
            {
                if (p != people[i])
                {
                    // a collision
                    if (p->getBounds().intersects(people[i]->getBounds()))
                    {
                        p->becomeInfected();
                    }
                }
            }
        }
        
        people[i]->checkHealth();
        /*____________________________________________________________________*/
    }
}

