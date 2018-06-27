/*
  ==============================================================================

    LFO.h
    Created: 6 May 2018 11:00:07am
    Author:  Thomas Barrett

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "ProcessorBase.h"

class LFO : public ProcessorBase, public AudioProcessorValueTreeState::Listener
{
public:
    LFO();
    const String getName() const override { return "LFO"; }
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages) override;
    void reset() override;
    void parameterChanged(const String& parameterID, float newValue) override;
private:
    dsp::Oscillator<float> oscillator;
};
