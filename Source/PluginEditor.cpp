/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
JuceSynthFrameworkAudioProcessorEditor::JuceSynthFrameworkAudioProcessorEditor (JuceSynthFrameworkAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p), osc1 (p), env1 (p)
    //synthOscLabel({ }, processor.oscSelector->name)
{
    setSize (400, 200);
    addAndMakeVisible(&env1);
    addAndMakeVisible(&osc1);   
}

JuceSynthFrameworkAudioProcessorEditor::~JuceSynthFrameworkAudioProcessorEditor()
{
}

//==============================================================================
void JuceSynthFrameworkAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void JuceSynthFrameworkAudioProcessorEditor::resized()
{
    Rectangle <int> area = getLocalBounds();
    
    const int sectionWidth = 200;
    const int sectionHeight = 200;
    osc1.setBounds(area.removeFromLeft(sectionWidth).removeFromTop(sectionHeight));
    env1.setBounds (area.removeFromLeft(sectionWidth).removeFromTop(sectionHeight));
}





