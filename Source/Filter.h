/*
  ==============================================================================

    Filter.h
    Created: 1 Jan 2018 1:51:01pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthVoice.h"
#include "PluginProcessor.h"
#include "maximilian.h"

//==============================================================================
/*
*/
class Filter    : public AudioProcessorEditor,
                  public Slider::Listener,
                  private ComboBox::Listener
{
public:
    Filter(JuceSynthFrameworkAudioProcessor&);
    ~Filter();

    void paint (Graphics&) override;
    void resized() override;
    
    void comboBoxChanged(ComboBox*) override;
    void sliderValueChanged(Slider*) override;
    
    double getFilterType (double input, float filterCutoff, float filterResonance);
    
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> filterType;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> cutoff;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> resonance;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceSynthFrameworkAudioProcessor& processor;
    
    ComboBox filterBox;
    
    maxiFilter filter;
    
    Slider filterDial;
    Slider resonanceDial;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
