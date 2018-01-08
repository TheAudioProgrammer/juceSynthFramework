/*
  ==============================================================================

    SynthSound.h
    Created: 29 Oct 2017 10:18:47am
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"



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
