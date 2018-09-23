/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TomSirenAudioProcessor::TomSirenAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withOutput("Output", AudioChannelSet::stereo(), true)
                       ),
        mainProcessor(new AudioProcessorGraph()),
        parameters(*this, nullptr)
{
    parameters.createAndAddParameter("sine_freq", "Sine LFO Freq", String(), NormalisableRange<float>(0.01f, 100.0f), 4.0f, nullptr, nullptr);
    parameters.createAndAddParameter("sine_amount", "Sine LFO Amount", String(), NormalisableRange<float>(0.01f, 1000.0f), 4.0f, nullptr, nullptr);
    parameters.createAndAddParameter("saw_freq", "Saw LFO Amount", String(), NormalisableRange<float>(0.01f, 100.0f), 4.0f, nullptr, nullptr);
    parameters.createAndAddParameter("saw_amount", "Saw LFO Amount", String(), NormalisableRange<float>(0.01f, 1000.0f), 4.0f, nullptr, nullptr);
    parameters.createAndAddParameter("base_freq", "Base Freq", String(), NormalisableRange<float>(20.0f, 2000.0f), 440.0f, nullptr, nullptr);
    parameters.state = ValueTree(Identifier("TomSiren"));
}

TomSirenAudioProcessor::~TomSirenAudioProcessor() { }

//==============================================================================
const String TomSirenAudioProcessor::getName() const { return "TomSiren"; }
bool TomSirenAudioProcessor::acceptsMidi() const { return true; }
bool TomSirenAudioProcessor::producesMidi() const { return false; }
bool TomSirenAudioProcessor::isMidiEffect() const { return false; }
double TomSirenAudioProcessor::getTailLengthSeconds() const { return 0.0; }
int TomSirenAudioProcessor::getNumPrograms() { return 1; }
int TomSirenAudioProcessor::getCurrentProgram() { return 0; }
void TomSirenAudioProcessor::setCurrentProgram (int index) { }
const String TomSirenAudioProcessor::getProgramName (int index) { return {}; }
void TomSirenAudioProcessor::changeProgramName (int index, const String& newName) { }

//==============================================================================
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
    for (auto paramID : freqParamIDs) {
        parameters.removeParameterListener(paramID, static_cast<Siren*>(baseNode->getProcessor()));
    }

    mainProcessor->releaseResources();
}

bool TomSirenAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() == AudioChannelSet::disabled())
        return false;
    
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;
    
    return true;
}

void TomSirenAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    for (int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); i++)
    {
        buffer.clear(i, 0, buffer.getNumSamples());
    }
    
    mainProcessor->processBlock(buffer, midiMessages);
}

void TomSirenAudioProcessor::initialiseGraph()
{
    mainProcessor->clear();
    
    audioOutputNode = mainProcessor->addNode(new AudioGraphIOProcessor(AudioGraphIOProcessor::audioOutputNode));
    midiInputNode = mainProcessor->addNode(new AudioGraphIOProcessor(AudioGraphIOProcessor::midiInputNode));
    midiOutputNode = mainProcessor->addNode(new AudioGraphIOProcessor(AudioGraphIOProcessor::midiOutputNode));
    
    baseNode = mainProcessor->addNode(new Siren{parameters});
    
    baseNode->getProcessor()->enableAllBuses();
    
    for (auto paramID : freqParamIDs) {
        parameters.addParameterListener(paramID, static_cast<Siren*>(baseNode->getProcessor()));
    }

    connectAudioNodes();
    connectMidiNodes();
}

void TomSirenAudioProcessor::connectAudioNodes()
{
    for (int channel = 0; channel < 2; ++channel)
    {
        mainProcessor->addConnection({
            { baseNode->nodeID, channel },
            { audioOutputNode->nodeID, channel }
        });
    }
}

void TomSirenAudioProcessor::connectMidiNodes()
{
    mainProcessor->addConnection({
        { midiInputNode->nodeID, AudioProcessorGraph::midiChannelIndex},
        { midiOutputNode->nodeID, AudioProcessorGraph::midiChannelIndex}
    });
}

//==============================================================================

AudioProcessorEditor* TomSirenAudioProcessor::createEditor()
{
    return new TomSirenAudioProcessorEditor (*this, parameters);
}

bool TomSirenAudioProcessor::hasEditor() const { return true; }
void TomSirenAudioProcessor::getStateInformation (MemoryBlock& destData) { }
void TomSirenAudioProcessor::setStateInformation (const void* data, int sizeInBytes) { }

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TomSirenAudioProcessor();
}
