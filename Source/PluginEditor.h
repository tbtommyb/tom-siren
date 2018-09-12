/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Oscillator.h"

//==============================================================================

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
    
    // TODO listen to UI events, update valueTreeState with params
    // LFO rate, LFO amp, base freq etc
    AudioProcessorValueTreeState& valueTreeState;
    
    Label lfoFreqLabel;
    Slider lfoFreq;
    std::unique_ptr<SliderAttachment> lfoFreqAttachment;
    
    Label lfoAmountLabel;
    Slider lfoAmount;
    std::unique_ptr<SliderAttachment> lfoAmmountAttachment;
    
    Label baseFreqLabel;
    Slider baseFreq;
    std::unique_ptr<SliderAttachment> baseFreqAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TomSirenAudioProcessorEditor)
};
