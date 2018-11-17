/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Oscillator.h"
#include "Oscillator2.h"
#include "Envelope.h"
#include "Filter.h"
#include "Frontgui.h"


//==============================================================================
/**
*/
class JuceSynthFrameworkAudioProcessorEditor  : public AudioProcessorEditor

{
public:
    JuceSynthFrameworkAudioProcessorEditor (JuceSynthFrameworkAudioProcessor&);
    ~JuceSynthFrameworkAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    
    Oscillator oscGui;
    Oscillator2 osc2Gui;
    Envelope envGui;
    Filter filterGui;
    Frontgui frontGui;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceSynthFrameworkAudioProcessorEditor)
};
