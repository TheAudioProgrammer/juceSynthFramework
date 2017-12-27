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
    
    //=======================================================
    
    void getWaveType (int* oscId)
    {
        theWave = *oscId;
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
            if (theWave == 1)
            {
                oscWaveType = osc1.sinewave(frequency);
            }
            
            if (theWave == 2)
            {
                oscWaveType = osc1.saw(frequency);
            }
            
            double theSound = env1.adsr(oscWaveType, env1.trigger) * level * 0.2f;
            
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, theSound);
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
    maxiOsc osc1;
    maxiEnv env1;
    
    
    
};
