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


class SynthVoice : public SynthesiserVoice
{    
public:
    double filterCutoff = 100;
    double filterResonance = 1.0;
    
    
    //=======================================================
    
    bool canPlaySound (SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    
    //=======================================================
    
    void getParam (float* attack, float* decay, float* sustain, float* release)
    {
        env1.setAttack(double(*attack));
        env1.setDecay(double(*decay));
        env1.setSustain(double(*sustain));
        env1.setRelease(double(*release));
    }
    
    void getFilterParam (float* _filterCutoff, float* _filterResonance)
    {
        filterCutoff = (double) *_filterCutoff;
        filterResonance = (double) *_filterResonance;
    }
    
    //=======================================================
    
    void getWaveType (int* oscId)
    {
        theWave = *oscId;
    }
    
    //=======================================================
    
    void getFilterType (int* filterId)
    {
        theFilter = *filterId;
    }
    
    //=======================================================
    
    double setFilterType (double input, double filterCutoff, double filterResonance)
    {
        if (theFilter == 1)
            return filter.lores(input, filterCutoff, filterResonance);
        else
            return filter.hires(input, filterCutoff, filterResonance);
    }
    
    //=======================================================
    
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        env1.trigger = 1;
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        level = velocity;
    }
    
    //=======================================================
    
    void stopNote (float velocity, bool allowTailOff)
    {
        env1.trigger = 0;
        
        allowTailOff = true;
        
        if (velocity == 0)
            clearCurrentNote();
    }
    
    //=======================================================
    
    void renderNextBlock (AudioBuffer <float> &outputBuffer, int startSample, int numSamples)
    {
        
        
        for (int sample = 0; sample < numSamples; ++sample)
        {
          
            double currentFrame = 0;
            
            //change oscillators...
            if (theWave == 1)
            {
                oscWaveType = osc1.sinewave(frequency);
            }
            
            if (theWave == 2)
            {
                oscWaveType = osc1.saw(frequency);
            }
            
            currentFrame = env1.adsr(oscWaveType, env1.trigger) * level * 0.2f;
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
    double level;
    double frequency;
    double oscWaveType;
    
    
    int theWave = 1;
    int theFilter = 1;
    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter;
    
};
