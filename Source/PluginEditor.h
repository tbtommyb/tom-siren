/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TomSirenAudioProcessorEditor  : public AudioProcessorEditor,
private Slider::Listener
{
public:
    TomSirenAudioProcessorEditor (TomSirenAudioProcessor&);
    ~TomSirenAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    void sliderValueChanged (Slider* slider) override;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TomSirenAudioProcessor& processor;
    
    Slider midiVolume;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TomSirenAudioProcessorEditor)
};
