/*
  ==============================================================================

    WavetableOsc.h
    Created: 1 May 2018 10:22:24pm
    Author:  Thomas Barrett

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class WavetableOsc
{
public:
    WavetableOsc(const AudioSampleBuffer& wavetable);
    ~WavetableOsc();
    void setFrequency(float frequency, float sampleRate);
    forcedinline float getNextSample() noexcept;
private:
    const AudioSampleBuffer& wavetable;
    const int tableSize;
    float currentIndex = 0.0f, tableDelta = 0.0f;
    
};
