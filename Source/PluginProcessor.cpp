/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SineOsc.h"
#include "WavetableOsc.h"
#include "LFO.h"

//==============================================================================
TomSirenAudioProcessor::TomSirenAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                       ),
        mainProcessor(new AudioProcessorGraph()),
        lfoFreq(new AudioParameterFloat("lfo_freq",
                                        "LFO Freq",
                                        NormalisableRange<float>(0.0f, 10000.0f),
                                        200.0f))
#endif
{
    addParameter(lfoFreq);
}

TomSirenAudioProcessor::~TomSirenAudioProcessor()
{
}

//==============================================================================
const String TomSirenAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TomSirenAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TomSirenAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TomSirenAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TomSirenAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TomSirenAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TomSirenAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TomSirenAudioProcessor::setCurrentProgram (int index)
{
}

const String TomSirenAudioProcessor::getProgramName (int index)
{
    return {};
}

void TomSirenAudioProcessor::changeProgramName (int index, const String& newName)
{
}

void TomSirenAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mainProcessor->setPlayConfigDetails(getMainBusNumInputChannels(),
                                        getMainBusNumOutputChannels(),
                                        sampleRate, samplesPerBlock);
    
    mainProcessor->prepareToPlay(sampleRate, samplesPerBlock);
    
    initialiseGraph();
}

void TomSirenAudioProcessor::releaseResources()
{
    mainProcessor->releaseResources();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TomSirenAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() == AudioChannelSet::disabled()) {
        return false;
    }
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo()) {
        return false;
    }
    return layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet();
}
#endif

void TomSirenAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    for (int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); i++)
    {
        buffer.clear(i, 0, buffer.getNumSamples());
    }
    
    mainProcessor->processBlock(buffer, midiMessages);
}
    
//    ScopedNoDenormals noDenormals;
//    auto totalNumInputChannels  = getTotalNumInputChannels();
//    auto totalNumOutputChannels = getTotalNumOutputChannels();
//
//    MidiBuffer processedMidi;
//    int time;
//    MidiMessage m;
//
//    for (MidiBuffer::Iterator i{midiMessages}; i.getNextEvent(m, time);)
//    {
//        if (m.isNoteOn())
//        {
//            uint8 newVel = (uint8)noteOnVel;
//            m = MidiMessage::noteOn(m.getChannel(), m.getNoteNumber(), newVel);
//        }
//        else if (m.isNoteOff())
//        {
//        }
//        else if (m.isAftertouch())
//        {
//        }
//        else if (m.isPitchWheel())
//        {
//        }
//
//        processedMidi.addEvent(m, time);
//    }
//    midiMessages.swapWith(processedMidi);
//
//    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
//        buffer.clear (i, 0, buffer.getNumSamples());
//
//    for (int channel = 0; channel < totalNumInputChannels; ++channel)
//    {
//        auto* channelData = buffer.getWritePointer (channel);
//    }

void TomSirenAudioProcessor::initialiseGraph()
{
    mainProcessor->clear();
    
    audioOutputNode = mainProcessor->addNode(new AudioGraphIOProcessor(AudioGraphIOProcessor::audioOutputNode));
    midiInputNode = mainProcessor->addNode(new AudioGraphIOProcessor(AudioGraphIOProcessor::midiInputNode));
    midiOutputNode = mainProcessor->addNode(new AudioGraphIOProcessor(AudioGraphIOProcessor::midiOutputNode));
    lfoNode = mainProcessor->addNode(new LFO());
    
    for (int channel = 0; channel < 2; channel++)
    {
        mainProcessor->addConnection({ { lfoNode->nodeID, channel },
                                       { audioOutputNode->nodeID, channel }
        });
    }
}

void TomSirenAudioProcessor::connectAudioNodes()
{
}

void TomSirenAudioProcessor::connectMidiNodes()
{
    mainProcessor->addConnection({
        { midiInputNode->nodeID, AudioProcessorGraph::midiChannelIndex},
        { midiOutputNode->nodeID, AudioProcessorGraph::midiChannelIndex}
    });
}

//==============================================================================
bool TomSirenAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TomSirenAudioProcessor::createEditor()
{
    return new TomSirenAudioProcessorEditor (*this);
}

//==============================================================================
void TomSirenAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TomSirenAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TomSirenAudioProcessor();
}
