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
    
    sineFreqLbl.setText("Sine Freq", dontSendNotification);
    sineAmountLbl.setText("Sine Amount", dontSendNotification);
    sawFreqLbl.setText("Saw Freq", dontSendNotification);
    sawAmountLbl.setText("Saw Amount", dontSendNotification);
    baseFreqLbl.setText("Base Freq", dontSendNotification);
    
    addAndMakeVisible(sineFreqLbl);
    addAndMakeVisible(sineFreq);

    addAndMakeVisible(sineAmountLbl);
    addAndMakeVisible(sineAmount);
    
    addAndMakeVisible(sawFreqLbl);
    addAndMakeVisible(sawFreq);

    addAndMakeVisible(sawAmountLbl);
    addAndMakeVisible(sawAmount);
    
    addAndMakeVisible(baseFreqLbl);
    addAndMakeVisible(baseFreq);
    
    sineFreqAttachment.reset(new SliderAttachment(valueTreeState, "sine_freq", sineFreq));
    sineAmountAttachment.reset(new SliderAttachment(valueTreeState, "sine_amount", sineAmount));

    sawFreqAttachment.reset(new SliderAttachment(valueTreeState, "saw_freq", sawFreq));
    sawAmountAttachment.reset(new SliderAttachment(valueTreeState, "saw_amount", sawAmount));

    baseFreqAttachment.reset(new SliderAttachment(valueTreeState, "base_freq", baseFreq));

    sineFreq.setSkewFactorFromMidPoint(20.0f);
    sineAmount.setSkewFactorFromMidPoint(300.0f);
    
    sawFreq.setSkewFactorFromMidPoint(20.0f);
    sawAmount.setSkewFactorFromMidPoint(300.0f);

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

    auto sliderHeight = 60;
    auto labelMargin = 80;

    auto baseRect = r.removeFromTop(sliderHeight);
    baseFreqLbl.setBounds(baseRect.removeFromLeft(labelMargin));
    baseFreq.setBounds(baseRect);

    auto sineLFORect = r.removeFromTop(sliderHeight);
    sineFreqLbl.setBounds(sineLFORect.removeFromLeft(labelMargin));
    sineFreq.setBounds(sineLFORect);

    auto sineLFOAmountRect = r.removeFromTop(sliderHeight);
    sineAmountLbl.setBounds(sineLFOAmountRect.removeFromLeft(labelMargin));
    sineAmount.setBounds(sineLFOAmountRect);
    
    auto sawLFORect = r.removeFromTop(sliderHeight);
    sawFreqLbl.setBounds(sawLFORect.removeFromLeft(labelMargin));
    sawFreq.setBounds(sawLFORect);
    
    auto sawLFOAmountRect = r.removeFromTop(sliderHeight);
    sawAmountLbl.setBounds(sawLFOAmountRect.removeFromLeft(labelMargin));
    sawAmount.setBounds(sawLFOAmountRect);
}
