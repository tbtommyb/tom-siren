/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "LFO.h"

//==============================================================================
/**
*/
class TomSirenAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    
    TomSirenAudioProcessorEditor (TomSirenAudioProcessor&, AudioProcessorValueTreeState&);
    ~TomSirenAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TomSirenAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;
    
    Label lfoFreqLabel;
    Slider lfoFreq;
    std::unique_ptr<SliderAttachment> lfoFreqAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TomSirenAudioProcessorEditor)
};
