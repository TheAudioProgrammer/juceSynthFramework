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
        env1.setAttack(.2);
        env1.setDecay(500);
        env1.setSustain(0.8);
        env1.setRelease(2000.0);
        
        for (int sample = 0; sample < numSamples; ++sample)
        {
            double theWave = osc1.sinewave(frequency);
            double theSound = env1.adsr(theWave, env1.trigger) * level;
            
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
    
    maxiOsc osc1;
    maxiEnv env1;

    
    
    
};
