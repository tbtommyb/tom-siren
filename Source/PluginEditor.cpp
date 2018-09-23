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
    
    sineLFOFreqLabel.setText("LFO Freq", dontSendNotification);
    sineLFOAmountLabel.setText("LFO Amount", dontSendNotification);
    sawLFOFreqLabel.setText("Saw Freq", dontSendNotification);
    sawLFOAmountLabel.setText("Saw Amount", dontSendNotification);
    baseFreqLabel.setText("Base Freq", dontSendNotification);
    
    addAndMakeVisible(sineLFOFreqLabel);
    addAndMakeVisible(sineLFOFreq);

    addAndMakeVisible(sineLFOAmountLabel);
    addAndMakeVisible(sineLFOAmount);
    
    addAndMakeVisible(sawLFOFreqLabel);
    addAndMakeVisible(sawLFOFreq);

    addAndMakeVisible(sawLFOAmountLabel);
    addAndMakeVisible(sawLFOAmount);
    
    addAndMakeVisible(baseFreqLabel);
    addAndMakeVisible(baseFreq);
    
    sineLFOFreqAttachment.reset(new SliderAttachment(valueTreeState, "sine_lfo_freq", sineLFOFreq));
    sineLFOAmountAttachment.reset(new SliderAttachment(valueTreeState, "sine_lfo_amount", sineLFOAmount));

    sawLFOFreqAttachment.reset(new SliderAttachment(valueTreeState, "saw_lfo_freq", sawLFOFreq));
    sawLFOAmountAttachment.reset(new SliderAttachment(valueTreeState, "saw_lfo_amount", sawLFOAmount));

    baseFreqAttachment.reset(new SliderAttachment(valueTreeState, "base_freq", baseFreq));

    sineLFOFreq.setSkewFactorFromMidPoint(20.0f);
    sineLFOAmount.setSkewFactorFromMidPoint(300.0f);
    
    sawLFOFreq.setSkewFactorFromMidPoint(20.0f);
    sawLFOAmount.setSkewFactorFromMidPoint(300.0f);

    baseFreq.setSkewFactorFromMidPoint(500.f);
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
    
    // TODO find the proper way to do this
    auto sineLFORect = r.removeFromTop(40);
    sineLFOFreqLabel.setBounds(sineLFORect.removeFromLeft(80));
    sineLFOFreq.setBounds(sineLFORect);

    auto sineLFOAmountRect = r.removeFromTop(60);
    sineLFOAmountLabel.setBounds(sineLFOAmountRect.removeFromLeft(80));
    sineLFOAmount.setBounds(sineLFOAmountRect);
    
    auto sawLFORect = r.removeFromTop(80);
    sawLFOFreqLabel.setBounds(sawLFORect.removeFromLeft(80));
    sawLFOFreq.setBounds(sawLFORect);
    
    auto sawLFOAmountRect = r.removeFromTop(60);
    sawLFOAmountLabel.setBounds(sawLFOAmountRect.removeFromLeft(80));
    sawLFOAmount.setBounds(sawLFOAmountRect);
    
    auto baseRect = r.removeFromTop(100);
    baseFreqLabel.setBounds(baseRect.removeFromLeft(80));
    baseFreq.setBounds(baseRect);
    
}
