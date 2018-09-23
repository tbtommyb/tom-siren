/*
  ==============================================================================

    LFO.cpp
    Created: 6 May 2018 11:00:07am
    Author:  Thomas Barrett

  ==============================================================================
*/

#include "Siren.h"
#include <iostream>

Siren::Siren(const String& identifier, const String& name)
: identifier(identifier), name(name)
{
    processorChain.template get<outputIndex>().setFrequency(440.f);
    processorChain.template get<outputIndex>().initialise([] (float x) { return std::sin(x); }, 128);
    
    sineLFO.initialise ([] (float x) { return std::sin (x); }, 128);
    sineLFO.setFrequency(4.0f);
    lfoAmount = 4.0f;
    baseFreq = 440.0f;
}

void Siren::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    dsp::ProcessSpec spec { sampleRate, static_cast<uint32> (samplesPerBlock) };
    processorChain.prepare (spec);
    sineLFO.prepare (spec);
}

void Siren::processBlock (AudioSampleBuffer& buffer, MidiBuffer&)
{
    auto lfoOut = sineLFO.processSample(0.0f);
    auto lfoFreq = jmap(lfoOut, -1.0f, 1.0f, 0.0f, lfoAmount);
    
    processorChain.template get<outputIndex>().setFrequency(baseFreq + lfoFreq);
    dsp::AudioBlock<float> block (buffer);
    dsp::ProcessContextReplacing<float> context (block);
    
    sineLFO.process (context);
    processorChain.process (context);
}

void Siren::reset()
{
    processorChain.reset();
}

void Siren::parameterChanged(const String& parameterID, float newValue)
{
    if (parameterID == "base_freq") {
        baseFreq = newValue;
    }
    
    if (parameterID == "sine_lfo_freq") {
        sineLFO.setFrequency(newValue);
    }
    
    if (parameterID == "sine_lfo_amount") {
        lfoAmount = newValue;
    }
}
