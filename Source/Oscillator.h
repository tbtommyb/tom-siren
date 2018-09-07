/*
  ==============================================================================

    Oscillator.h
    Created: 6 May 2018 11:00:07am
    Author:  Thomas Barrett

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "ProcessorBase.h"

class Oscillator : public ProcessorBase, public AudioProcessorValueTreeState::Listener
{
public:
    Oscillator(const String& identifier, const String& name);
    const String getName() const override { return name; }
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages) override;
    void reset() override;
    void parameterChanged(const String& parameterID, float newValue) override;
private:
    dsp::Oscillator<float> oscillator;
    const String identifier;
    const String name;
};
