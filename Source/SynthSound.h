/*
  ==============================================================================

    SynthSound.h
    Created: 29 Oct 2017 10:18:47am
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


//this is necessary to use the synthesizer class in juce (help from juce forum)
class SynthSound : public SynthesiserSound
{

public:
    bool appliesToNote (int midiNoteNumber) override
    {
        return true;
    }
    
    bool appliesToChannel (int midiNoteNumber) override
    {
        return true;
    }
    
    
    
    
    
    
};
