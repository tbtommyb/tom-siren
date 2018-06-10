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
    
    midiVolume.setSliderStyle(Slider::LinearBarVertical);
    midiVolume.setRange(0., 127., 1.);
    midiVolume.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    midiVolume.setPopupDisplayEnabled(true, false, this);
    midiVolume.setTextValueSuffix(" Volume");
    midiVolume.setValue(1.0);
    
    midiVolume.addListener(this);
    
    addAndMakeVisible(&midiVolume);
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
    g.drawFittedText("Midi volume", 0, 0, getWidth(), 30, Justification::centred, 1);
}

void TomSirenAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    midiVolume.setBounds(40, 30, 20, getHeight() - 60);
}

void TomSirenAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    processor.noteOnVel = midiVolume.getValue();
}
