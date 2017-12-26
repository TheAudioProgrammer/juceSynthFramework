/*
  ==============================================================================

    SynthOsc.h
    Created: 26 Dec 2017 8:28:43pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class SynthOsc    : public AudioProcessorEditor,
                    private ComboBox::Listener
{
public:
    SynthOsc(JuceSynthFrameworkAudioProcessor&);
    ~SynthOsc();

    void paint (Graphics&) override;
    void resized() override;
    
    void comboBoxChanged(ComboBox*) override;
    
    //double getWaveType (double frequency);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    
    ComboBox synthBox;
    
    maxiOsc osc1;
    
    ScopedPointer <AudioProcessorValueTreeState::ComboBoxAttachment> waveType;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthOsc)
};
