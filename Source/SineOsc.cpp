/*
  ==============================================================================

    SineOsc.cpp
    Created: 1 May 2018 10:59:05pm
    Author:  Thomas Barrett

  ==============================================================================
*/

#include "SineOsc.h"

SineOsc::SineOsc(int tableSize) : tableSize(tableSize)
{
    initBuffer();
};

WavetableOsc SineOsc::create()
{
    return WavetableOsc{buffer};
}

void SineOsc::initBuffer()
{
    AudioSampleBuffer buffer;
    buffer.setSize(1, tableSize + 1);
    auto* samples = buffer.getWritePointer(0);
    
    auto angleDelta = MathConstants<double>::twoPi / (double) (tableSize - 1);
    auto currentAngle = 0.0;
    
    for (auto i = 0; i < tableSize; ++i)
    {
        auto sample = std::sin(currentAngle);
        samples[i] = (float) sample;
        currentAngle += angleDelta;
    }
    samples[tableSize] = samples[0];
}
