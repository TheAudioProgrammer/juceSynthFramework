/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthVoice.h"
#include "SynthSound.h"


//==============================================================================
/**
*/
class JuceSynthFrameworkAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    JuceSynthFrameworkAudioProcessor();
    ~JuceSynthFrameworkAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //don't think I actually need these since I'm getting values from the tree state, but afraid to delete them
    float attackTime;
    float decayTime;
    float sustainTime;
    float releaseTime;
    float filterCutoff;
    float filterResonance;
    
    //tree state holds all param values to save or recall, or automate in a daw
    AudioProcessorValueTreeState tree;
    
    //selector for wave osc type
    ScopedPointer <AudioParameterChoice> oscSelector;
    
    //need these to use a synth in juce! (help frum juce tutorials)
    Synthesiser mySynth;
    SynthVoice* myVoice;

private:
    
    
    double lastSampleRate;
    

    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceSynthFrameworkAudioProcessor)
};
