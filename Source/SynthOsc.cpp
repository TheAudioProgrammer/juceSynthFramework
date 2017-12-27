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
    //synthBox.addItem("Square", 3);
    
    
    waveType = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree, "wavetype", synthBox);
    
    synthBox.addListener(this);
    addAndMakeVisible(synthBox);
}

SynthOsc::~SynthOsc()
{
}

void SynthOsc::paint (Graphics& g)
{
    Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    g.drawText("Oscillator One", titleArea, Justification::centredTop);
    
    
    Rectangle <float> area (25, 25, 150, 150);
    
    g.setColour(Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void SynthOsc::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(50);
    
    synthBox.setBounds(area.removeFromTop(30));
}

void SynthOsc::comboBoxChanged(ComboBox *box)
{
    auto index = synthBox.getSelectedItemIndex() + 1;
    
    if (box == &synthBox)
    {
        int* theSelection = &index;
        
        for (int i = 0; i < processor.mySynth.getNumVoices(); i++)
        {
            if ((processor.myVoice = dynamic_cast<SynthVoice*>(processor.mySynth.getVoice(i))))
            {
                processor.myVoice->getWaveType(theSelection);
            }
        }
    }
}

