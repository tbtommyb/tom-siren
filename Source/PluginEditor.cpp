/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TomSirenAudioProcessorEditor::TomSirenAudioProcessorEditor (TomSirenAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 150);
    
    lfoFreq.setSliderStyle(Slider::LinearBarVertical);
    lfoFreq.setRange(200., 4000., 1.);
    lfoFreq.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    lfoFreq.setPopupDisplayEnabled(true, false, this);
    lfoFreq.setTextValueSuffix(" Hz");
    lfoFreq.setValue(200.0);
    
    lfoFreq.addListener(this);
    
    addAndMakeVisible(&lfoFreq);
}

TomSirenAudioProcessorEditor::~TomSirenAudioProcessorEditor()
{
}

//==============================================================================
void TomSirenAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(Colours::white);
    
    g.setColour(Colours::black);

    g.setFont (15.0f);
    g.drawFittedText("LFO freq", 0, 0, getWidth(), 30, Justification::centred, 1);
}

void TomSirenAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    lfoFreq.setBounds(40, 30, 20, getHeight() - 60);
}

void TomSirenAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    auto lfo = static_cast<LFO*>(processor.lfoNode->getProcessor());
    lfo->setFrequency(slider->getValue());
}
