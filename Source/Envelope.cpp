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
    setSize(200, 200);
    
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
    Rectangle<int> titleArea = getLocalBounds().removeFromTop(20);
    
    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    g.drawText("Envelope", titleArea, Justification::centredTop);
    
}

void Envelope::resized()
{
    Rectangle<int> area = getLocalBounds();
    
    int sliderWidth = 50;
    int sliderHeight = 150;
    
    attackSlider.setBounds (area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(20));
    decaySlider.setBounds (area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(20));
    sustainSlider.setBounds (area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(20));
    releaseSlider.setBounds (area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(20));

}

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
