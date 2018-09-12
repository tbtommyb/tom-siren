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
    lfoAmountLabel.setText("LFO Amount", dontSendNotification);
    baseFreqLabel.setText("Base Freq", dontSendNotification);
    
    addAndMakeVisible(lfoFreqLabel);
    addAndMakeVisible(lfoFreq);

    addAndMakeVisible(lfoAmountLabel);
    addAndMakeVisible(lfoAmount);

    addAndMakeVisible(baseFreqLabel);
    addAndMakeVisible(baseFreq);
    
    lfoFreqAttachment.reset(new SliderAttachment(valueTreeState, "lfo_freq", lfoFreq));
    lfoAmmountAttachment.reset(new SliderAttachment(valueTreeState, "lfo_amount", lfoAmount));
    baseFreqAttachment.reset(new SliderAttachment(valueTreeState, "base_freq", baseFreq));

    lfoFreq.setSkewFactorFromMidPoint(20.0f);
    lfoAmount.setSkewFactorFromMidPoint(300.0f);
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
    
    auto lfoRect = r.removeFromTop(40);
    lfoFreqLabel.setBounds(lfoRect.removeFromLeft(80));
    lfoFreq.setBounds(lfoRect);
    // TODO find the proper way to do this
    auto lfoAmountRect = r.removeFromTop(60);
    lfoAmountLabel.setBounds(lfoAmountRect.removeFromLeft(80));
    lfoAmount.setBounds(lfoAmountRect);
    
    auto baseRect = r.removeFromTop(100);
    baseFreqLabel.setBounds(baseRect.removeFromLeft(80));
    baseFreq.setBounds(baseRect);
    
}
