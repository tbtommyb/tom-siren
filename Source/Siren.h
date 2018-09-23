/*
  ==============================================================================

    Siren.h
    Created: 6 May 2018 11:00:07am
    Author:  Thomas Barrett

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "ProcessorBase.h"
#include "Distortion.h"
#include "CustomOscillator.h"

class Siren : public ProcessorBase, public AudioProcessorValueTreeState::Listener
{
public:
    Siren(const AudioProcessorValueTreeState& parameters);
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages) override;
    void reset() override;
    void parameterChanged(const String& parameterID, float newValue) override;

private:
    enum {
        outputIndex,
        distortionIndex
    };
    dsp::ProcessorChain<dsp::Oscillator<float>, Distortion<float>> processorChain;
    CustomOscillator<float> sineLFO;
    CustomOscillator<float> sawLFO;
        
    static constexpr size_t lfoUpdateRate = 100;
    size_t lfoUpdateCounter = lfoUpdateRate;
    
    float sineRate, sineAmount, sawRate, sawAmount;

    float baseFreq;
    
    const AudioProcessorValueTreeState& parameters;
};
