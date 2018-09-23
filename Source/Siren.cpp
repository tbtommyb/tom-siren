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
    
    sineLFO.setWaveform(CustomOscillator<float>::Waveform::sine);
    sineLFO.setFrequency(4.0f);
    
    sawLFO.setWaveform(CustomOscillator<float>::Waveform::saw);
    sawLFO.setFrequency(4.0f);
    
    sineLFOAmount = 4.0f;
    sawLFOAmount = 4.0f;
    baseFreq = 440.0f;
}

void Siren::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    dsp::ProcessSpec spec { sampleRate, static_cast<uint32> (samplesPerBlock), 2 };
    sineLFO.prepare(spec);
    sawLFO.prepare(spec);
    processorChain.prepare(spec);
}

void Siren::processBlock (AudioSampleBuffer& buffer, MidiBuffer&)
{
    auto sineLFOSample = sineLFO.processSample(0.0f);
    auto sineLFOFreq = jmap(sineLFOSample, -1.0f, 1.0f, 0.0f, sineLFOAmount);
    
    auto sawLFOSample = sawLFO.processSample(0.0f);
    auto sawLFOFreq = jmap(sawLFOSample, -1.0f, 1.0f, 0.0f, sawLFOAmount);
    
    processorChain.template get<outputIndex>().setFrequency(baseFreq + sineLFOFreq + sawLFOFreq);
    dsp::AudioBlock<float> block (buffer);
    dsp::ProcessContextReplacing<float> context (block);
    
    sineLFO.process(context);
    sawLFO.process(context);
    processorChain.process(context);
}

void Siren::reset()
{
    processorChain.reset();
    sineLFO.reset();
    sawLFO.reset();
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
        sineLFOAmount = newValue;
    }
    
    if (parameterID == "saw_lfo_freq") {
        sawLFO.setFrequency(newValue);
    }
    
    if (parameterID == "saw_lfo_amount") {
        sawLFOAmount = newValue;
    }
}
