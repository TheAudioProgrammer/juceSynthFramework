/*
  ==============================================================================

    Envelope.h
    Created: 23 Dec 2017 6:08:05pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Envelope    : public AudioProcessorEditor,
                    public Slider::Listener
{
public:
    Envelope(JuceSynthFrameworkAudioProcessor&);
    ~Envelope();
    
    //==============================================================================
    
    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged (Slider* slider) override;
    
    

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    
    //these relay slider values back to the processor tree state.  Scoped Pointer deletes itself when out of scope
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> attackTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> decayTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> sustainTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> releaseTree;
    
    //slider objects
    Slider attackSlider;
    Slider decaySlider;
    Slider sustainSlider;
    Slider releaseSlider;
};
