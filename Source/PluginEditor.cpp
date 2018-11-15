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
    : AudioProcessorEditor (&p), processor (p), oscGui(p), envGui(p), filterGui(p)
{
    setSize (600, 200);
    
    addAndMakeVisible(&oscGui);
    addAndMakeVisible(&envGui);
    addAndMakeVisible(&filterGui);
}

JuceSynthFrameworkAudioProcessorEditor::~JuceSynthFrameworkAudioProcessorEditor()
{
}

//==============================================================================
void JuceSynthFrameworkAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::black);
}

void JuceSynthFrameworkAudioProcessorEditor::resized()
{
    juce::Rectangle<int> area = getLocalBounds();
    
    const int componentWidth = 200;
    const int componentHeight = 200;
    
    oscGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    filterGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    envGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    
    

}


