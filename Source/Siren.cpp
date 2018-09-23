/*
  ==============================================================================

    LFO.cpp
    Created: 6 May 2018 11:00:07am
    Author:  Thomas Barrett

  ==============================================================================
*/

#include "Siren.h"
#include <iostream>

Siren::Siren(const AudioProcessorValueTreeState& parameters)
: parameters(parameters)
{
    auto* baseFreq = parameters.getRawParameterValue("base_freq");
    processorChain.template get<outputIndex>().setFrequency(*baseFreq);
    processorChain.template get<outputIndex>().initialise([] (float x) { return std::sin(x); }, 128);
    
    sineLFO.setWaveform(CustomOscillator<float>::Waveform::sine);
    sineLFO.setFrequency(4.0f);
    sineLFO.setLevel(0.0f);
    
    sawLFO.setWaveform(CustomOscillator<float>::Waveform::saw);
    sawLFO.setFrequency(4.0f);
    sawLFO.setLevel(0.0f);
    
    sineAmount = 4.0f;
    sawAmount = 4.0f;
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
    auto* baseFreq = parameters.getRawParameterValue("base_freq");

    auto sineSample = sineLFO.processSample(0.0f);
    auto sineFreq = jmap(sineSample, -1.0f, 1.0f, 0.0f, sineAmount);
    
    auto sawSample = sawLFO.processSample(0.0f);
    auto sawFreq = jmap(sawSample, -1.0f, 1.0f, 0.0f, sawAmount);
    
    processorChain.template get<outputIndex>().setFrequency(*baseFreq + sineFreq + sawFreq);
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
    } else if (parameterID == "sine_lfo_freq") {
        sineLFO.setFrequency(newValue);
    } else if (parameterID == "sine_lfo_amount") {
        sineAmount = newValue;
    } else if (parameterID == "saw_lfo_freq") {
        sawLFO.setFrequency(newValue);
    } else if (parameterID == "saw_lfo_amount") {
        sawAmount = newValue;
    }
}
