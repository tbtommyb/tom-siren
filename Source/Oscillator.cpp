/*
  ==============================================================================

    LFO.cpp
    Created: 6 May 2018 11:00:07am
    Author:  Thomas Barrett

  ==============================================================================
*/

#include "Oscillator.h"

Oscillator::Oscillator(const String& identifier, const String& name)
: identifier(identifier), name(name)
{
    oscillator.setFrequency (440.0f);
    oscillator.initialise ([] (float x) { return std::sin (x); });
    
    lfo.setFrequency (4.0f);
    lfo.initialise ([] (float x) { return std::sin (x); });
}

void Oscillator::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    dsp::ProcessSpec spec { sampleRate, static_cast<uint32> (samplesPerBlock) };
    oscillator.prepare (spec);
    lfo.prepare (spec);
}

void Oscillator::processBlock (AudioSampleBuffer& buffer, MidiBuffer&)
{
    auto lfoOut = lfo.processSample(0.0f);
    oscillator.setFrequency(oscillator.getFrequency() + (lfoOut * 20));
    dsp::AudioBlock<float> block (buffer);
    dsp::ProcessContextReplacing<float> context (block);
    oscillator.process (context);
    lfo.process (context);
}

void Oscillator::reset()
{
    oscillator.reset();
}

void Oscillator::parameterChanged(const String& parameterID, float newValue)
{
    if (parameterID == identifier) {
        oscillator.setFrequency(newValue);
    }
    
    if (parameterID == "lfo_freq") {
        lfo.setFrequency(newValue);
    }
}
