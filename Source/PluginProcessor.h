/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
class TomSirenAudioProcessor  : public AudioProcessor
{
public:
    using AudioGraphIOProcessor = AudioProcessorGraph::AudioGraphIOProcessor;
    
    float noteOnVel;

    //==============================================================================
    TomSirenAudioProcessor();
    ~TomSirenAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    std::unique_ptr<AudioProcessorGraph> mainProcessor;
    
    void initialiseGraph();
    void connectAudioNodes();
    void connectMidiNodes();
    
    AudioProcessorGraph::Node::Ptr audioOutputNode;
    AudioProcessorGraph::Node::Ptr midiInputNode;
    AudioProcessorGraph::Node::Ptr midiOutputNode;
    
    AudioProcessorGraph::Node::Ptr lfoNode;
    
    AudioParameterFloat* lfoFreq;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TomSirenAudioProcessor)
};
