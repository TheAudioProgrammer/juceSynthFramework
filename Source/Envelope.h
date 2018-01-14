/*
  ==============================================================================

    Envelope.h
    Created: 11 Jan 2018 2:31:07pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Envelope    : public Component
{
public:
    Envelope(JuceSynthFrameworkAudioProcessor&);
    ~Envelope();

    void paint (Graphics&) override;
    void resized() override;
    

private:
    Slider attackSlider;
    Slider decaySlider;
    Slider sustainSlider;
    Slider releaseSlider;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sustainVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> releaseVal;
    
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
