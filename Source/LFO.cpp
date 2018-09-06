/*
  ==============================================================================

    LFO.cpp
    Created: 6 May 2018 11:00:07am
    Author:  Thomas Barrett

  ==============================================================================
*/

#include "LFO.h"

LFO::LFO()
{
    oscillator.setFrequency (440.0f);
    oscillator.initialise ([] (float x) { return std::sin (x); });
}

void LFO::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    dsp::ProcessSpec spec { sampleRate, static_cast<uint32> (samplesPerBlock) };
    oscillator.prepare (spec);
}

void LFO::processBlock (AudioSampleBuffer& buffer, MidiBuffer&)
{
    dsp::AudioBlock<float> block (buffer);
    dsp::ProcessContextReplacing<float> context (block);
    oscillator.process (context);
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
