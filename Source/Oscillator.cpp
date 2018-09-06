/*
  ==============================================================================

    LFO.cpp
    Created: 6 May 2018 11:00:07am
    Author:  Thomas Barrett

  ==============================================================================
*/

#include "Oscillator.h"

Oscillator::Oscillator()
{
    oscillator.setFrequency (440.0f);
    oscillator.initialise ([] (float x) { return std::sin (x); });
}

void Oscillator::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    dsp::ProcessSpec spec { sampleRate, static_cast<uint32> (samplesPerBlock) };
    oscillator.prepare (spec);
}

void Oscillator::processBlock (AudioSampleBuffer& buffer, MidiBuffer&)
{
    dsp::AudioBlock<float> block (buffer);
    dsp::ProcessContextReplacing<float> context (block);
    oscillator.process (context);
}

void Oscillator::reset()
{
    oscillator.reset();
}

void Oscillator::parameterChanged(const String& parameterID, float newValue)
{
    if (parameterID == "lfo_freq") {
        oscillator.setFrequency(newValue);
    }
}
