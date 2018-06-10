/*
  ==============================================================================

    WavetableOsc.cpp
    Created: 1 May 2018 10:22:24pm
    Author:  Thomas Barrett

  ==============================================================================
*/

#include "WavetableOsc.h"

WavetableOsc::WavetableOsc(const AudioSampleBuffer& wavetable)
: wavetable(wavetable), tableSize(wavetable.getNumSamples() - 1)
{
    jassert(wavetable.getNumChannels() == 1);
};

WavetableOsc::~WavetableOsc()
{
};

void WavetableOsc::setFrequency(float frequency, float sampleRate)
{
    auto tableSizeOverSampleRate = tableSize / sampleRate;
    tableDelta = frequency * tableSizeOverSampleRate;
};

forcedinline float WavetableOsc::getNextSample() noexcept
{
    auto tableSize = wavetable.getNumSamples();
    auto index0 = (unsigned int) currentIndex;
    auto index1 = index0 + 1;
    
    auto frac = currentIndex - (float) index0;
    auto* table = wavetable.getReadPointer(0);
    
    auto value0 = table[index0];
    auto value1 = table[index1];
    
    auto currentSample = value0 + frac * (value1 - value0);
    if ((currentIndex += tableDelta) > tableSize) {
        currentIndex -= tableSize;
    }
    
    return currentSample;
};

