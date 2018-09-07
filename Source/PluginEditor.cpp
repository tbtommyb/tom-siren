/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TomSirenAudioProcessorEditor::TomSirenAudioProcessorEditor (TomSirenAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (p), processor (p), valueTreeState(vts)
{
    setSize (400, 300);
    
    lfoFreqLabel.setText("LFO Freq", dontSendNotification);
    baseFreqLabel.setText("Base Freq", dontSendNotification);
    
    addAndMakeVisible(lfoFreqLabel);
    addAndMakeVisible(baseFreqLabel);
    addAndMakeVisible(lfoFreq);
    addAndMakeVisible(baseFreq);
    lfoFreqAttachment.reset(new SliderAttachment(valueTreeState, "lfo_freq", lfoFreq));
    baseFreqAttachment.reset(new SliderAttachment(valueTreeState, "base_freq", baseFreq));
}

TomSirenAudioProcessorEditor::~TomSirenAudioProcessorEditor() { }

//==============================================================================
void TomSirenAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void TomSirenAudioProcessorEditor::resized()
{
    auto r = getLocalBounds();
    
    auto lfoRect = r.removeFromTop(40);
    lfoFreqLabel.setBounds(lfoRect.removeFromLeft(80));
    lfoFreq.setBounds(lfoRect);
    
    auto baseRect = r.removeFromTop(100);
    baseFreqLabel.setBounds(baseRect.removeFromLeft(80));
    baseFreq.setBounds(baseRect);
}
