/*
  ==============================================================================

    SynthVoice.h
    Created: 29 Oct 2017 10:18:29am
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


class SynthVoice : public SynthesiserVoice
{
    
public:
    bool canPlaySound (SynthesiserSound* sound) override
    {
        return dynamic_cast <SynthVoice*>(sound) != nullptr;
    }
    
    //=======================================================
    
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        
    }
    
    //=======================================================
    
    void stopNote (float velocity, bool allowTailOff)
    {
        
    }
    
    //=======================================================
    
    void pitchWheelMoved (int newPitchWheelValue)
    {
        
    }
    
    //=======================================================
    
    void controllerMoved (int controllerNumber, int newControllerValue)
    {
        
    }
    
    //=======================================================
    
    void renderNextAudioBlock (AudioBuffer <double> &outputBuffer, int startSample, int numSamples)
    {
        
    }
    
    
    
    
};
