/*
  ==============================================================================

    LFO.cpp
    Created: 6 May 2018 11:00:07am
    Author:  Thomas Barrett

  ==============================================================================
*/

#include "Oscillator.h"
#include <iostream>

Oscillator::Oscillator(const String& identifier, const String& name)
: identifier(identifier), name(name)
{
    output.setFrequency (440.0f);
    output.initialise ([] (float x) { return std::sin (x); }, 128);
    
    lfo.setFrequency (4.0f);
    lfo.initialise ([] (float x) { return std::sin (x); }, 128);
    
    lfoAmount = 4.0f;
    baseFreq = 440.0f;
}

void Oscillator::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    dsp::ProcessSpec spec { sampleRate, static_cast<uint32> (samplesPerBlock) };
    //dsp::ProcessSpec lfoSpec { sampleRate / lfoUpdateRate, static_cast<uint32>(samplesPerBlock)};
    output.prepare (spec);

    // Using this version sounds bad
    //lfo.prepare (lfoSpec);
    lfo.prepare(spec);
}

void Oscillator::processBlock (AudioSampleBuffer& buffer, MidiBuffer&)
{
    auto lfoOut = lfo.processSample(0.0f);

    output.setFrequency(baseFreq + (lfoOut * lfoAmount));
    dsp::AudioBlock<float> block (buffer);
    dsp::ProcessContextReplacing<float> context (block);
    output.process (context);
    lfo.process (context);
}

void Oscillator::reset()
{
    output.reset();
}

void Oscillator::parameterChanged(const String& parameterID, float newValue)
{
    if (parameterID == "base_freq") {
        baseFreq = newValue;
    }
    
    if (parameterID == "lfo_freq") {
        lfo.setFrequency(newValue);
    }
    
    if (parameterID == "lfo_amount") {
        lfoAmount = newValue;
    }
}
