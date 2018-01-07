/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
JuceSynthFrameworkAudioProcessor::JuceSynthFrameworkAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
attackTime(0.1f),
tree (*this, nullptr)
#endif
{
    //The audio processor value tree state allows us to create automatable parameters in any daw and understand what we're controlling!  It also creates a link between the gui side of the plugin and the processing side
    
    
    //envelope normalisable range for processor tree
    NormalisableRange<float> attackRange (0.1f, 5000.0f);
    NormalisableRange<float> decayRange (0.1f, 5000.0f);
    NormalisableRange<float> sustainRange (0.0f, 1.0f);
    NormalisableRange<float> releaseRange (0.1f, 5000.0f);
    
    //envelope parameters for processor tree
    tree.createAndAddParameter("attack", "Attack", "Attack", attackRange, 0.7f, nullptr, nullptr);
    tree.createAndAddParameter("decay", "Decay", "Decay", decayRange, 2000.0f, nullptr, nullptr);
    tree.createAndAddParameter("sustain", "Sustain", "Sustain", sustainRange, 1.0f, nullptr, nullptr);
    tree.createAndAddParameter("release", "Release", "Release", releaseRange, 1000.0f, nullptr, nullptr);
    
    //wave and filter type param
    NormalisableRange<float> wavetypeRange (1, 3);
    NormalisableRange<float> filtertypeRange (1, 3);
    NormalisableRange<float> modFreqRange (0.0f, 1000.0f);
    NormalisableRange<float> modDepthRange (0.0f, 1000.0f);
    NormalisableRange<float> filterCutoffRange (20.0f, 15000.0f);
    filterCutoffRange.setSkewForCentre(800);
    NormalisableRange<float> filterResonanceRange (1.0f, 4.0f);
    
    //wavetype, filtertype, and filter params
    tree.createAndAddParameter("wavetype", "Wavetype", "Wavetype", wavetypeRange, 0, nullptr, nullptr);
    tree.createAndAddParameter("filtertype", "Filtertype", "Filtertype", filtertypeRange, 0, nullptr, nullptr);
    tree.createAndAddParameter("filterCutoff", "FilterCutoff", "FilterCutoff", filterCutoffRange, 200.0f, nullptr, nullptr);
    tree.createAndAddParameter("filterResonance", "FilterResonance", "FilterResonance", filterResonanceRange, 1.0f, nullptr, nullptr);
    
    //mod osc
    tree.createAndAddParameter("modFreq", "ModFreq", "ModFreq", modFreqRange, 0.0f, nullptr, nullptr);
    tree.createAndAddParameter("modDepth", "ModDepth", "ModDepth", modDepthRange, 0.0f, nullptr, nullptr);
    
    //used for xml- save the state of the tree for recall
    tree.state = ValueTree ("savedParams");
    
    //clear any voices that may be lingering (help from juce synth example)
    mySynth.clearVoices();
    
    //creates 5 voice polyphony (help from juce synth example)
    for (int i = 0; i < 5; i++)
    {
        mySynth.addVoice (new SynthVoice());
    }
    
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
}

JuceSynthFrameworkAudioProcessor::~JuceSynthFrameworkAudioProcessor()
{
}

//==============================================================================
const String JuceSynthFrameworkAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JuceSynthFrameworkAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JuceSynthFrameworkAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JuceSynthFrameworkAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JuceSynthFrameworkAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JuceSynthFrameworkAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JuceSynthFrameworkAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JuceSynthFrameworkAudioProcessor::setCurrentProgram (int index)
{
}

const String JuceSynthFrameworkAudioProcessor::getProgramName (int index)
{
    return {};
}

void JuceSynthFrameworkAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void JuceSynthFrameworkAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
}

void JuceSynthFrameworkAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JuceSynthFrameworkAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void JuceSynthFrameworkAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    
    
    for (int i = 0; i < mySynth.getNumVoices(); i++)
    {
        /*(help from Juce synth example) if the the voice is sucessfully cast as a synthvoice pointer,
        get the parameters needed to create the voice from the synthvoice class
         */
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))))
        {
            myVoice->getParam(tree.getRawParameterValue("attack"),
                              tree.getRawParameterValue("decay"),
                              tree.getRawParameterValue("sustain"),
                              tree.getRawParameterValue("release"));
            
            myVoice->getFilterParam(tree.getRawParameterValue("filterCutoff"),
                                    tree.getRawParameterValue("filterResonance"));
            
            myVoice->getModOscParam(tree.getRawParameterValue("modFreq"),
                                    tree.getRawParameterValue("modDepth"));
        }
    }
    
    
    
    //clear lingering junk
    buffer.clear();
    
    //play the sounds
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool JuceSynthFrameworkAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* JuceSynthFrameworkAudioProcessor::createEditor()
{
    return new JuceSynthFrameworkAudioProcessorEditor (*this);
}

//==============================================================================
void JuceSynthFrameworkAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    //(help from juce tutorials) create xml object pointer to get all state information
    ScopedPointer<XmlElement> xml (tree.state.createXml());
    copyXmlToBinary(*xml, destData);
}

void JuceSynthFrameworkAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    //create an xml from the binary info (help from juce tutorials)
    ScopedPointer<XmlElement> theParams (getXmlFromBinary(data, sizeInBytes));
    
    //(help from juce tutorials) safeguard if there's no xml
    if (theParams != nullptr)
    {
        if (theParams->hasTagName(tree.state.getType()))
        {
            tree.state = ValueTree::fromXml(*theParams);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JuceSynthFrameworkAudioProcessor();
}
