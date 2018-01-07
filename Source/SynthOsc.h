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
#include "SynthSound.h"
#include "SynthVoice.h"

//==============================================================================
/*
*/
class SynthOsc    : public AudioProcessorEditor,
                    private ComboBox::Listener,
                    public Slider::Listener
{
public:
    SynthOsc(JuceSynthFrameworkAudioProcessor&);
    ~SynthOsc();

    void paint (Graphics&) override;
    void resized() override;
    
    void comboBoxChanged(ComboBox*) override;
    void sliderValueChanged(Slider*) override;
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    
    //combobox to switch osc type, and dials for mod frequency and mod depth
    ComboBox synthBox;
    Slider modFreq;
    Slider modDepth;
    
    //oscillator object
    maxiOsc osc1;
    
    //these relay slider values back to the processor tree state.  Scoped Pointer deletes itself when out of scope
    ScopedPointer <AudioProcessorValueTreeState::ComboBoxAttachment> waveType;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> modFreqParam;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> modDepthParam;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthOsc)
};
