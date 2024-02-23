/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluginWeek3AudioProcessorEditor::PluginWeek3AudioProcessorEditor (PluginWeek3AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //
    mSlider.setRange(0, 1.f); //set slider range
    addAndMakeVisible(mSlider); //make slider visible
    //set slider style
    mSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    //set text box style
    mSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 20);
    mSlider.onValueChange = [this] () {
        audioProcessor.setGainValue(mSlider.getValue());
    };
    //

    
    
    
    setResizable(true,true);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

PluginWeek3AudioProcessorEditor::~PluginWeek3AudioProcessorEditor()
{
}

//==============================================================================
void PluginWeek3AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Assignment 3: Volume Slider", getLocalBounds(), juce::Justification::centred, 1);
}

void PluginWeek3AudioProcessorEditor::resized()
{
    mSlider.setBounds(0,0,getWidth(),getHeight());
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
