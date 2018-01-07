/*
  ==============================================================================

    SynthVoice.h
    Created: 29 Oct 2017 10:18:29am
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "Maximilian.h"
#include "SynthVoice.h"


//need this class to use juce synthesizer class...contains all properties needed to play a synthesizer voice (help from juce forum)
class SynthVoice : public SynthesiserVoice
{    
public:
    //global variables I need to grab values from classes and set
    float filterCutoff = 200;
    float filterResonance = 1.0;
    float modFreq = 0;
    float modDepth = 0;
    
    //=======================================================
    
    //returns true if the synthsound is dynamically cast
    bool canPlaySound (SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    
    //=======================================================
   
    //gets envelope settings from process block in Plugin Processor
    void getParam (float* attack, float* decay, float* sustain, float* release)
    {
        env1.setAttack(double(*attack));
        env1.setDecay(double(*decay));
        env1.setSustain(double(*sustain));
        env1.setRelease(double(*release));
    }
    //gets and updates filter settings from process block in Plugin Processor
    void getFilterParam (float* _filterCutoff, float* _filterResonance)
    {
        filterCutoff = (float) *_filterCutoff;
        filterResonance = (float) *_filterResonance;
    }
    
    //=======================================================
    //listen for changes in the combobox that sets the wave type
    void getWaveType (int* oscId)
    {
        theWave = *oscId;
    }
    
    //=======================================================
    //sets the wave type from getWaveType()
    double setWaveType ()
    {
        //change oscillators...adding fm capability
        if (theWave == 1)
            return oscWaveType = osc1.sinewave(frequency + (modOsc1.sinewave(modFreq) * modDepth));
        
        else
            return oscWaveType = osc1.saw(frequency + (modOsc1.sinewave(modFreq) * modDepth));
    }
    
    //=======================================================
    
    //gets and updates mod osc settings from process block in Plugin Processor
    void getModOscParam (float* _modFreq, float* _modDepth)
    {
        modFreq = *_modFreq;
        modDepth = *_modDepth;
    }
    
    //=======================================================
    //listens for changes in filter type from combo box
    void getFilterType (int* filterId)
    {
        theFilter = *filterId;
    }
    
    //=======================================================
    //sets changes from getFilterType()
    double setFilterType (double input, float filterCutoff, float filterResonance)
    {
        if (theFilter == 1)
            return filter.lores(input, filterCutoff, filterResonance);
        else
            return filter.hires(input, filterCutoff, filterResonance);
    }
    
    //=======================================================
    //what happens when I press a note?
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        env1.trigger = 1;
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        level = velocity;
    }
    
    //=======================================================
    //what happens when I stop pressing the note?
    void stopNote (float velocity, bool allowTailOff)
    {
        env1.trigger = 0;
        
        allowTailOff = true;
        
        if (velocity == 0)
            clearCurrentNote();
    }
    
    //=======================================================
    
    //routing for the synth that goes inside the process block in Plugin Processor
    void renderNextBlock (AudioBuffer <float> &outputBuffer, int startSample, int numSamples)
    {
        for (int sample = 0; sample < numSamples; ++sample)
        {
            double currentFrame = 0;
            
            //get the wave type
            currentFrame = setWaveType();
            //put it in the envelope
            currentFrame = env1.adsr(currentFrame, env1.trigger) * level * 0.2f;
            //route the envelope into the filter
            currentFrame = setFilterType (currentFrame, filterCutoff, filterResonance);
            
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, currentFrame);
            }
            ++startSample;
        }
    }
    
    void pitchWheelMoved (int newPitchWheelValue)
    {
    
    }
    
    //=======================================================
    
    void controllerMoved (int controllerNumber, int newControllerValue)
    {
        
    }
    
    //=======================================================
    
    
    
private:
    //variables I need to pass around to keep these things working
    double level;
    double frequency;
    double oscWaveType;
    int theWave = 1;
    int theFilter = 1;
    maxiOsc osc1;
    
    //maximilian objects
    maxiOsc modOsc1;
    maxiEnv env1;
    maxiFilter filter;
    
};
