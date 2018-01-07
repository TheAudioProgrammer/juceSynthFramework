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
: AudioProcessorEditor (&p), processor (p), osc1 (p), env1 (p), filter1 (p)
    //synthOscLabel({ }, processor.oscSelector->name)
{
    //hold env, osc and filter ui as child components and make them visible in this component
    setSize (600, 200);
    addAndMakeVisible(&env1);
    addAndMakeVisible(&osc1);
    addAndMakeVisible(&filter1);
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
    //create a rectangle the same size as the component we're in (600, 200)
    Rectangle <int> area = getLocalBounds();
    
    //create measurements so we can scale ui dynamically
    const int sectionWidth = 200;
    const int sectionHeight = 200;
    
    //draw osc, filter, and env ui
    osc1.setBounds(area.removeFromLeft(sectionWidth).removeFromTop(sectionHeight));
    filter1.setBounds (area.removeFromLeft(sectionWidth).removeFromTop(sectionHeight));
    env1.setBounds (area.removeFromLeft(sectionWidth).removeFromTop(sectionHeight));
    
}





