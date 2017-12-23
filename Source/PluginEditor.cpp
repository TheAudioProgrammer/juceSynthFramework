/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
JuceSynthFrameworkAudioProcessorEditor::JuceSynthFrameworkAudioProcessorEditor (JuceSynthFrameworkAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.1f, 5000.0f);
    attackSlider.setValue(0.5f);
    //attackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
    attackSlider.addListener(this);
    addAndMakeVisible(&attackSlider);
    
    decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(0.1f, 5000.0f);
    decaySlider.setValue(0.5f);
    decaySlider.addListener(this);
    addAndMakeVisible(&decaySlider);
    
    sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.0f, 1.0f);
    sustainSlider.setValue(1.0f);
    sustainSlider.addListener(this);
    addAndMakeVisible(&sustainSlider);
    
    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.1f, 5000.0f);
    releaseSlider.setValue(1000.0f);
    releaseSlider.addListener(this);
    addAndMakeVisible(&releaseSlider);
    
    
    attackTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "attack", attackSlider);
    decayTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "decay", decaySlider);
    sustainTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "sustain", sustainSlider);
    releaseTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "release", releaseSlider);
}

JuceSynthFrameworkAudioProcessorEditor::~JuceSynthFrameworkAudioProcessorEditor()
{
}

//==============================================================================
void JuceSynthFrameworkAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void JuceSynthFrameworkAudioProcessorEditor::resized()
{
    attackSlider.setBounds (10, 10, 40, 100);
    decaySlider.setBounds (60, 10, 40, 100);
    sustainSlider.setBounds (110, 10, 40, 100);
    releaseSlider.setBounds (160, 10, 40, 100);
}

void JuceSynthFrameworkAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &attackSlider)
    {
        processor.attackTime = attackSlider.getValue();
    }
    
    if (slider == &decaySlider)
    {
        processor.decayTime = decaySlider.getValue();
    }
    
    if (slider == &sustainSlider)
    {
        processor.sustainTime = decaySlider.getValue();
    }
    
    if (slider == &releaseSlider)
    {
        processor.releaseTime = releaseSlider.getValue();
    }
}



