/*
  ==============================================================================

    LFO.cpp
    Created: 6 May 2018 11:00:07am
    Author:  Thomas Barrett

  ==============================================================================
*/

#include <iostream>
#include "LFO.h"

LFO::LFO()
{
    std::cout << "CREATING OSCILLATOR ***************" << std::endl;
    oscillator.setFrequency(200.0);
    oscillator.initialise([] (float x) { return std::sin(x); });
}

void LFO::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    dsp::ProcessSpec spec { sampleRate, static_cast<uint32>(samplesPerBlock) };
    oscillator.prepare(spec);
}

void LFO::processBlock(AudioSampleBuffer &buffer, juce::MidiBuffer &midiMessages)
{
    dsp::AudioBlock<float> block(buffer);
    dsp::ProcessContextReplacing<float> context(block);
    oscillator.process(context);
}

void LFO::reset()
{
    oscillator.reset();
}

void LFO::parameterChanged(const String& parameterID, float newValue)
{
    if (parameterID == "lfo_freq") {
        oscillator.setFrequency(newValue);
    }
}

