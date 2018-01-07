/*
  ==============================================================================

    SynthOsc.cpp
    Created: 26 Dec 2017 8:28:43pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthOsc.h"

//==============================================================================
SynthOsc::SynthOsc(JuceSynthFrameworkAudioProcessor& p) :
AudioProcessorEditor (&p), processor (p)
{
    setSize(200, 200);
    
    //combobox used to set waveform type
    synthBox.setJustificationType(Justification::centred);
    
    //add items to combobox
    synthBox.addItem("Sine", 1);
    synthBox.addItem("Saw", 2);
    //synthBox.addItem("Square", 3);
    
    //slider stuff (set values etc)
    modFreq.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    modFreq.setRange(0, 1000);
    modFreq.setValue(0);
    modFreq.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    modFreq.addListener(this);
    addAndMakeVisible(modFreq);
    
    modDepth.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    modDepth.setRange(0, 1000);
    modDepth.setValue(0);
    modDepth.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    modDepth.addListener(this);
    addAndMakeVisible(modDepth);
    
    //relay the slider values back to the tree state in processor
    waveType = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree, "wavetype", synthBox);
    modFreqParam = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "modFreq", modFreq);
    modDepthParam = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "modDepth", modDepth);
    
    //add this component as a listener for this combobox
    synthBox.addListener(this);
    addAndMakeVisible(synthBox);
}

SynthOsc::~SynthOsc()
{
}

void SynthOsc::paint (Graphics& g)
{
    //background stuff
    Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    g.drawText("Oscillator One", titleArea, Justification::centredTop);
    
    
    Rectangle <float> area (25, 25, 150, 150);
    
    g.setColour(Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void SynthOsc::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(40);
    synthBox.setBounds(area.removeFromTop(20));
    modFreq.setBounds (30, 100, 70, 70);
    modDepth.setBounds (100, 100, 70, 70);
}

//what happens when I change the option on the combobox?  Relay this info to synthvoice.  Pure virtual function that I needed to implement when inheriting from combobox
void SynthOsc::comboBoxChanged(ComboBox *box)
{
    //index starts from 1, not 0 for combobox class
    auto index = synthBox.getSelectedItemIndex() + 1;
    
    if (box == &synthBox)
    {
        int* theSelection = &index;
        
        //get the wavetype and relay this to my voice
        for (int i = 0; i < processor.mySynth.getNumVoices(); i++)
        {
            if ((processor.myVoice = dynamic_cast<SynthVoice*>(processor.mySynth.getVoice(i))))
            {
                processor.myVoice->getWaveType(theSelection);
            }
        }
    }
}

//pure virtual function but I left blank because values are being relayed via the value tree
void SynthOsc::sliderValueChanged(Slider* slider)
{
    if (slider == &modFreq)
    {
        
    }
    
    if (slider == &modDepth)
    {
        
    }
}

