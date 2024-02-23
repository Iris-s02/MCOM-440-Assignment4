/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class PluginWeek3AudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    PluginWeek3AudioProcessor();
    ~PluginWeek3AudioProcessor() override;

    
//AUDIO FUNCTIONS
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override; //Initialize your plugin
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    
    
    //SET GAIN FUNCTION
    void setGainValue(float inGain){
        //mSmoothedGain.setTargetValue(inGain);
        mGainParameter->setValueNotifyingHost(inGain);
    }
    
    float getGain() {
        //return mSmoothedGain.getTargetValue();
        return mGainParameter->get();
    }
    
    //about the plugin functions
    void releaseResources() override;

    
    
    
   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    
    
    
    
    
    
    
    //preset / state functions
    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginWeek3AudioProcessor)
    
    //float mGain = 1.f;
    
    juce::LinearSmoothedValue<float> mSmoothedGain;
    
    float mSineTonePhase = 0.1f;
    
    juce::AudioParameterFloat* mGainParameter;
    
    
    
    //==============================================================================
 
};
