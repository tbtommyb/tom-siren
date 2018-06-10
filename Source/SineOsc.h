/*
  ==============================================================================

    SineOsc.h
    Created: 1 May 2018 10:59:05pm
    Author:  Thomas Barrett

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "WavetableOsc.h"
#include <cmath>

class SineOsc {
public:
    SineOsc(int tableSize = 127);
    WavetableOsc create();
private:
    void initBuffer();
    int tableSize;
    AudioSampleBuffer buffer;
};
