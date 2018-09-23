/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Siren.h"

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

    AudioProcessorValueTreeState& valueTreeState;
    
    Label sineFreqLbl, sineAmountLbl, sawFreqLbl, sawAmountLbl, baseFreqLbl;
    Slider sineFreq, sineAmount, sawFreq, sawAmount, baseFreq;

    std::unique_ptr<SliderAttachment> sineFreqAttachment;
    std::unique_ptr<SliderAttachment> sineAmountAttachment;
    std::unique_ptr<SliderAttachment> sawFreqAttachment;
    std::unique_ptr<SliderAttachment> sawAmountAttachment;
    std::unique_ptr<SliderAttachment> baseFreqAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TomSirenAudioProcessorEditor)
};
