/*
  ==============================================================================

    Envelope.cpp
    Created: 23 Dec 2017 6:08:05pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(JuceSynthFrameworkAudioProcessor& p) :
AudioProcessorEditor (&p), processor (p)
{
    //Controls UI elements and relays any changes to synthvoice and processor
    
    
    setSize(200, 200);
    
    //the following is code I need to get a slider working in Juce, set values, add as a listener etc
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.1f, 5000.0f);
    attackSlider.setValue(0.5f);
    attackSlider.setTextBoxStyle(Slider::NoTextBox, false, 20.0, 10.0);
    attackSlider.addListener(this);
    addAndMakeVisible(&attackSlider);
    
    decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(0.1f, 5000.0f);
    decaySlider.setValue(0.5f);
    decaySlider.setTextBoxStyle(Slider::NoTextBox, false, 20.0, 10.0);
    decaySlider.addListener(this);
    addAndMakeVisible(&decaySlider);
    
    sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.0f, 1.0f);
    sustainSlider.setValue(1.0f);
    sustainSlider.setTextBoxStyle(Slider::NoTextBox, false, 20.0, 10.0);
    sustainSlider.addListener(this);
    addAndMakeVisible(&sustainSlider);
    
    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.1f, 5000.0f);
    releaseSlider.setValue(1000.0f);
    releaseSlider.setTextBoxStyle(Slider::NoTextBox, false, 20.0, 10.0);
    releaseSlider.addListener(this);
    addAndMakeVisible(&releaseSlider);
    
    //allows me to relay slider values from here to the value tree in the processor.  Says this slider means this param in the value tree
    attackTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "attack", attackSlider);
    decayTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "decay", decaySlider);
    sustainTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "sustain", sustainSlider);
    releaseTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "release", releaseSlider);
    
}

Envelope::~Envelope()
{
}

void Envelope::paint (Graphics& g)
{
    //fancy stuff for the UI background etc
    Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    g.drawText("Envelope", titleArea, Justification::centredTop);
    
    //static positioning for now due to time, make dynamic later
    g.drawText ("A", 53, 150, 20, 20, Justification::centredTop);
    g.drawText ("D", 77, 150, 20, 20, Justification::centredTop);
    g.drawText ("S", 103, 150, 20, 20, Justification::centredTop);
    g.drawText ("R", 128, 150, 20, 20, Justification::centredTop);
    
    Rectangle <float> area (25, 25, 150, 150);
    
    g.setColour(Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
    
}

void Envelope::resized()
{
    //draws the sliders...we use a rectangle object to dynamically size the UI (if we want to resize for IPad etc without needing to change ALL settings
    Rectangle<int> area = getLocalBounds().reduced(50);
    
    int sliderWidth = 25;
    int sliderHeight = 175;
    
    //draw sliders by reducing area from rectangle above
    attackSlider.setBounds (area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    decaySlider.setBounds (area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    sustainSlider.setBounds (area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    releaseSlider.setBounds (area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));

}

//pure virtual function that I need to implement, though the processor is actually grabbing these values via the value tree
void Envelope::sliderValueChanged(Slider* slider)
{
    if (slider == &attackSlider)
    {
        processor.attackTime = attackSlider.getValue();
    }
    
    if (slider == &decaySlider)
    {
        processor.decayTime = decaySlider.getValue();
    }
    
    if (slider == &sustainSlider)
    {
        processor.sustainTime = decaySlider.getValue();
    }
    
    if (slider == &releaseSlider)
    {
        processor.releaseTime = releaseSlider.getValue();
    }
}
