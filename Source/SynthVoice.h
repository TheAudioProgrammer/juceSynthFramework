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


class SynthVoice : public SynthesiserVoice
{
public:
    bool canPlaySound (SynthesiserSound* sound) override
    {
        return dynamic_cast <SynthSound*>(sound) != nullptr;
    }
    
    void getEnvelopeParams(float* attack, float* decay, float* sustain, float* release)
    {
        env1.setAttack(*attack);
        env1.setDecay(*decay);
        env1.setSustain(*sustain);
        env1.setRelease(*release);
    }
    
    //=======================================================
    
    void getOscType(float* selection)
    {
        theWave = *selection;
    }
    
    //=======================================================
    
    double setOscType ()
    {
        if (theWave == 0)
        {
            return osc1.sinewave(frequency);
        }
        
        if (theWave == 1)
        {
            return osc1.saw(frequency);
        }
        
        if (theWave == 2)
        {
            return osc1.square(frequency);
        }
        else
        {
            return osc1.sinewave(frequency);
        }
    }
    
    //=======================================================
    
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override
    {
        env1.trigger = 1;
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        level = velocity;
    }
    
    //=======================================================
    
    void stopNote (float velocity, bool allowTailOff) override
    {
        env1.trigger = 0;
        allowTailOff = true;
        
        if (velocity == 0)
            clearCurrentNote();
    }
    
    //=======================================================
    
    void pitchWheelMoved (int newPitchWheelValue) override
    {
        
    }
    
    //=======================================================
    
    void controllerMoved (int controllerNumber, int newControllerValue) override
    {
        
    }
    
    //=======================================================
    
    void renderNextBlock (AudioBuffer <float> &outputBuffer, int startSample, int numSamples) override
    {
        for (int sample = 0; sample < numSamples; ++sample)
        {
            //double theWave = osc1.sinewave(frequency);
            double theSound = env1.adsr(setOscType(), env1.trigger) * level;
            
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, theSound);
            }
            ++startSample;
        }
    }
    
    //=======================================================
private:
    double level;
    double frequency;
    int theWave;
    
    maxiOsc osc1;
    maxiEnv env1;

    
    
    
};
