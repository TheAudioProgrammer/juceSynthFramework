/*
  ==============================================================================

    SynthOsc.cpp
    Created: 26 Dec 2017 8:28:43pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthOsc.h"

//==============================================================================
SynthOsc::SynthOsc(JuceSynthFrameworkAudioProcessor& p) :
AudioProcessorEditor (&p), processor (p)
{
    setSize(200, 200);
    
    synthBox.setJustificationType(Justification::centred);
    synthBox.addItem("Sine", 1);
    synthBox.addItem("Saw", 2);
    synthBox.addItem("Square", 3);
    
    waveType = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree, "wavetype", synthBox);
    
    synthBox.addListener(this);
    addAndMakeVisible(synthBox);
}

SynthOsc::~SynthOsc()
{
}

void SynthOsc::paint (Graphics& g)
{
    Rectangle <int> titleArea = getLocalBounds().removeFromTop(20);
    
    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    g.drawText("Oscillator One", titleArea, Justification::centredTop);
}

void SynthOsc::resized()
{
    Rectangle <int> area = getLocalBounds().removeFromBottom(180);
    
    synthBox.setBounds(area.removeFromTop(30).removeFromLeft(75));
}

void SynthOsc::comboBoxChanged(ComboBox *box)
{
    auto index = synthBox.getSelectedItemIndex();
}

