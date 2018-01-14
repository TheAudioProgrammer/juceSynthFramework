/*
  ==============================================================================

    Filter.h
    Created: 14 Jan 2018 8:59:36pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter    : public Component
{
public:
    Filter(JuceSynthFrameworkAudioProcessor&);
    ~Filter();

    void paint (Graphics&) override;
    void resized() override;

private:
    Slider filterCutoff;
    Slider filterRes;
    
    ComboBox filterMenu;
    
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> resVal;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
