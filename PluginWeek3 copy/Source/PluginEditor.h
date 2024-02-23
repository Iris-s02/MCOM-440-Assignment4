/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class PluginWeek3AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    PluginWeek3AudioProcessorEditor (PluginWeek3AudioProcessor&);
    ~PluginWeek3AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    juce::Slider mSlider; //instantiate slider as a member
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginWeek3AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginWeek3AudioProcessorEditor)
};
