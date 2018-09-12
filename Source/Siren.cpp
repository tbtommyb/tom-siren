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
    
    lfo.initialise ([] (float x) { return std::sin (x); }, 128);
    lfo.setFrequency(4.0f);
    lfoAmount = 4.0f;
    baseFreq = 440.0f;
}

void Siren::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    dsp::ProcessSpec spec { sampleRate, static_cast<uint32> (samplesPerBlock) };
    processorChain.prepare (spec);
    lfo.prepare (spec);
}

void Siren::processBlock (AudioSampleBuffer& buffer, MidiBuffer&)
{
    auto lfoOut = lfo.processSample(0.0f);

    processorChain.template get<outputIndex>().setFrequency(baseFreq + (lfoOut * lfoAmount));
    dsp::AudioBlock<float> block (buffer);
    dsp::ProcessContextReplacing<float> context (block);
    
    lfo.process (context);
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
    
    if (parameterID == "lfo_freq") {
        lfo.setFrequency(newValue);
    }
    
    if (parameterID == "lfo_amount") {
        lfoAmount = newValue;
    }
}
