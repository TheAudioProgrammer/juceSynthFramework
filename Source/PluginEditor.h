/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class JuceSynthFrameworkAudioProcessorEditor  : public AudioProcessorEditor,
                                                public Slider::Listener
{
public:
    JuceSynthFrameworkAudioProcessorEditor (JuceSynthFrameworkAudioProcessor&);
    ~JuceSynthFrameworkAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged (Slider*) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    
    Slider attackSlider;
    Slider decaySlider;
    Slider sustainSlider;
    Slider releaseSlider;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sustainVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> releaseVal;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceSynthFrameworkAudioProcessorEditor)
};
