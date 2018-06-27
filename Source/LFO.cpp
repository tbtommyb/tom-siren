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
        std::cout << "parameter Id: " << parameterID << std::endl;
        std::cout << "newValue: " << newValue << std::endl;
        std::cout << "listener called" << std::endl;
        oscillator.setFrequency(newValue);
        std::cout << "after called" << std::endl;
        std::cout << oscillator.getFrequency() << std::endl;
    }
}

