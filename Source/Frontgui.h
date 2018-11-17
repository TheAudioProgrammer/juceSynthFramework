/*
 ==============================================================================
 
 Frontgui.h
 Created: 15 Nov 2018 7:44:02pm
 Author:  Dianne Campbell
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
 */
class Frontgui    : public Component
{
public:
    Frontgui(JuceSynthFrameworkAudioProcessor&);
    ~Frontgui();
    
    void paint (Graphics&) override;
    void resized() override;
    
    
private:
    Slider mastergainSlider;
    Slider pbupSlider;
    Slider pbdownSlider;
    
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mastergainVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> pbupVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> pbdownVal;
    
    
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Frontgui)
};
