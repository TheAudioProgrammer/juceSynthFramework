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
    //oscillator parameters
    
    
    //envelope normalisable range
    NormalisableRange<float> attackParam (0.1f, 5000.0f);
    NormalisableRange<float> decayParam (0.1f, 5000.0f);
    NormalisableRange<float> sustainParam (0.0f, 1.0f);
    NormalisableRange<float> releaseParam (0.1f, 5000.0f);
    
    //envelope parameters
    tree.createAndAddParameter("attack", "Attack", "Attack", attackParam, 0.7f, nullptr, nullptr);
    tree.createAndAddParameter("decay", "Decay", "Decay", decayParam, 2000.0f, nullptr, nullptr);
    tree.createAndAddParameter("sustain", "Sustain", "Sustain", sustainParam, 1.0f, nullptr, nullptr);
    tree.createAndAddParameter("release", "Release", "Release", releaseParam, 1000.0f, nullptr, nullptr);
    
    //wave type param
    NormalisableRange<float> wavetypeParam (0.0f, 2.0f);
    
    tree.createAndAddParameter("wavetype", "Wavetype", "Wavetype", wavetypeParam, 0.0f, nullptr, nullptr);
    
    tree.state = ValueTree ("savedParams");
    
    mySynth.clearVoices();
    
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
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))))
        {
            myVoice->getParam(tree.getRawParameterValue("attack"),
                              tree.getRawParameterValue("decay"),
                              tree.getRawParameterValue("sustain"),
                              tree.getRawParameterValue("release"));
            
            myVoice->getWaveType(tree.getRawParameterValue("wavetype"));
        }
    }
    
    
    
    
    buffer.clear();
    
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
    ScopedPointer<XmlElement> xml (tree.state.createXml());
    copyXmlToBinary(*xml, destData);
}

void JuceSynthFrameworkAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> theParams (getXmlFromBinary(data, sizeInBytes));
    
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
