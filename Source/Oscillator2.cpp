/*
  ==============================================================================

    Oscillator2.cpp
    Created: 16 Nov 2018 7:28:32pm
    Author:  Dianne Campbell

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator2.h"

//==============================================================================
Oscillator2::Oscillator2(JuceSynthFrameworkAudioProcessor& p) :
processor(p)
{
    setSize(200, 200);
    
    osc2Menu.addItem("Saw", 1);
    osc2Menu.addItem("Square", 2);
    osc2Menu.addItem("Sine", 3);
    osc2Menu.setJustificationType(Justification::centred);
    addAndMakeVisible(&osc2Menu);
    
    waveSelection2 = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree, "wavetype2", osc2Menu);
    
    //slider initialization values
    Blendslider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    Blendslider.setRange(0.0f, 1.0f);
    Blendslider.setValue(1.0f);
    Blendslider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&Blendslider);
    
    //sends value of the sliders to the tree state in the processor
    blendVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "blend", Blendslider);
}

Oscillator2::~Oscillator2()
{
}

void Oscillator2::paint (Graphics& g)
{
    //background stuff
    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    g.drawText("Oscillator Two", titleArea, Justification::centredTop);
    
    
    juce::Rectangle <float> area (25, 25, 150, 150);
    
    g.setColour(Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Oscillator2::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    osc2Menu.setBounds(area.removeFromTop(20));
    
    //draws the sliders...we use a rectangle object to dynamically size the UI (if we want to resize for IPad etc without needing to change ALL settings
    
    
    int sliderWidth = 25;
    int sliderHeight = 175;
    
    //draw sliders by reducing area from rectangle above
    Blendslider.setBounds (area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
}
