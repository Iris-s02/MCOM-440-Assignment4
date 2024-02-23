/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluginWeek3AudioProcessor::PluginWeek3AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameter (mGainParameter = new juce::AudioParameterFloat ("gain", // parameterID
                                                                  "Gain", // parameter name
                                                                  0.0f,   // minimum value
                                                                  1.0f,   // maximum value
                                                                  0.5f)); // default value
    
    mSmoothedGain.setCurrentAndTargetValue(0.5f);
}

PluginWeek3AudioProcessor::~PluginWeek3AudioProcessor()
{
}

//==============================================================================
const juce::String PluginWeek3AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PluginWeek3AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PluginWeek3AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PluginWeek3AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PluginWeek3AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginWeek3AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PluginWeek3AudioProcessor::getCurrentProgram()
{
    return 0;
}

void PluginWeek3AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String PluginWeek3AudioProcessor::getProgramName (int index)
{
    return {};
}

void PluginWeek3AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void PluginWeek3AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mSmoothedGain.reset(sampleRate, .01f);
    

}

void PluginWeek3AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PluginWeek3AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void PluginWeek3AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)

{
    //update the smoothed gain value
    mSmoothedGain.setTargetValue(mGainParameter->get());
    
    
    float* left_channel = buffer.getWritePointer(0);
    float* right_channel = buffer.getWritePointer(1);
    
    //smooth the gain value
    for (int sample_idx = 0; sample_idx < buffer.getNumSamples(); sample_idx++){
        float gain_value = mSmoothedGain.getNextValue();
        
        left_channel[sample_idx] *= gain_value;
        right_channel[sample_idx] *= gain_value;
    }
    
    float sine_hz = 80.f;
    float phase_delta = sine_hz / getSampleRate();
    
    //sine tone generator
    for (int sample_idx = 0; sample_idx < buffer.getNumSamples(); sample_idx++){
        
        float sine_out = std::sin(mSineTonePhase * 2 * M_PI);
        
        mSineTonePhase += phase_delta;
        
        if (mSineTonePhase > 1.f){
            mSineTonePhase -= 1.f;
        }
        
//        float gain_value = m
//
            left_channel[sample_idx] *= sine_out;
            right_channel[sample_idx] *= sine_out;
//
        
        
        
        
        
        
    }
    
    

    
//    int channel_left = 0;
//    int channel_right = 1;
    
    //per sample audio processing loop by value
//    for (sample_idx = 0; sample_idx < buffer.getNumSamples(); sample_idx++){
//
//        float gain_value = mSmoothedGain.getNextValue();
//
//        float sample_left = buffer.getSample(channel_left, sample_idx);
//        float sample_right = buffer.getSample(channel_right, sample_idx);
//
//        buffer.setSample(channel_left, sample_idx, sample_left * gain_value);
//        buffer.setSample(channel_right, sample_idx, sample_left * gain_value);
//    }
//
    
//
    
    
//    static float phase = 0;
//
//    for (int i = 0; i < buffer.getNumSamples(); i++){
//        float sine_out = std::sin(phase * 2 * M_PI);
//    }
    //Appy our gain to buffer
//    buffer.applyGain(mGain);
    
    
    
    
//    for (int channel = 0; channel < totalNumInputChannels; ++channel)
//    {
//        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }


//==============================================================================
bool PluginWeek3AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PluginWeek3AudioProcessor::createEditor()
{
    return new PluginWeek3AudioProcessorEditor (*this);
}

//==============================================================================
void PluginWeek3AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PluginWeek3AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginWeek3AudioProcessor();
}

