/*
  ==============================================================================

    Filter.cpp
    Created: 1 Jan 2018 1:51:01pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"

//==============================================================================
Filter::Filter(JuceSynthFrameworkAudioProcessor& p) :
AudioProcessorEditor (&p), processor (p)
{
    setSize(200, 200);
    
    //settings for filter box and add items
    filterBox.setJustificationType(Justification::centred);
    filterBox.addItem("Low-Pass", 1);
    filterBox.addItem("Hi-Pass", 2);
    filterBox.addListener(this);
    addAndMakeVisible(filterBox);
    
    //slider settings to get things working set values etc
    filterDial.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterDial.setRange(20.0f, 15000.0f);
    filterDial.setValue(200.0f);
    filterDial.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    filterDial.addListener(this);
    addAndMakeVisible(filterDial);
    
    resonanceDial.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    resonanceDial.setRange(1.0f, 4.0f);
    resonanceDial.setValue(0.2f);
    resonanceDial.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    resonanceDial.addListener(this);
    addAndMakeVisible(resonanceDial);
    
    //relays slider values to the processor tree state
    filterType = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree, "filtertype", filterBox);
    
    cutoff = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "filterCutoff", filterDial);
    
    resonance = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "filterResonance", resonanceDial);
}

Filter::~Filter()
{
}

void Filter::paint (Graphics& g)
{
    //background ui stuff
    Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    g.drawText("Filter", titleArea, Justification::centredTop);
    
    
    Rectangle <float> area (25, 25, 150, 150);
    
    g.setColour(Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Filter::resized()
{
    //need to come back and dynamically set these...ok for now
    Rectangle<int> area = getLocalBounds().reduced(40);
    
    filterBox.setBounds(area.removeFromTop(20));
    filterDial.setBounds (30, 100, 70, 70);
    resonanceDial.setBounds (100, 100, 70, 70);

}

//pure virtual function I needed to implement when inheriting from slider::listener
void Filter::sliderValueChanged(Slider* slider)
{
    if (slider == &filterDial)
    {
        //processor.myVoice->filterCutoff = filterDial.getValue();
    }
    
    if (slider == &resonanceDial)
    {
        //processor.myVoice->filterResonance = resonanceDial.getValue();
    }
    
}
//pure virtual function I needed to implement when inheriting from combobox
void Filter::comboBoxChanged(ComboBox *box)
{
    //combobox index starts at 1
    auto index = filterBox.getSelectedItemIndex() + 1;
    
    //relays combobox choice to synth voice
    if (box == &filterBox)
    {
        int* theSelection = &index;
        
        for (int i = 0; i < processor.mySynth.getNumVoices(); i++)
        {
            if ((processor.myVoice = dynamic_cast<SynthVoice*>(processor.mySynth.getVoice(i))))
            {
                processor.myVoice->getFilterType(theSelection);
            }
        }
    }
}




