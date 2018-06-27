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
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                       ),
        mainProcessor(new AudioProcessorGraph()),
        parameters(*this, nullptr)
#endif
{

    parameters.createAndAddParameter("lfo_freq", "LFO Freq", String(), NormalisableRange<float>(1.0f, 10000.0f), 200.0f, nullptr, nullptr);
    parameters.state = ValueTree(Identifier("LFOFreq"));

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
    if (lfoNode == nullptr) {
        mainProcessor->setPlayConfigDetails(getMainBusNumInputChannels(),
                                            getMainBusNumOutputChannels(),
                                            sampleRate, samplesPerBlock);
        
        mainProcessor->prepareToPlay(sampleRate, samplesPerBlock);
        initialiseGraph();
    }
}

void TomSirenAudioProcessor::releaseResources()
{
    std::cout << "releasing resources" << std::endl;
    parameters.removeParameterListener("lfo_freq", static_cast<LFO*>(lfoNode->getProcessor()));
    mainProcessor->releaseResources();
    lfoNode = nullptr;
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

void TomSirenAudioProcessor::initialiseGraph()
{
    std::cout << "CALLING INIT GRAPH" << std::endl;
    mainProcessor->clear();
    
    audioOutputNode = mainProcessor->addNode(new AudioGraphIOProcessor(AudioGraphIOProcessor::audioOutputNode));
    midiInputNode = mainProcessor->addNode(new AudioGraphIOProcessor(AudioGraphIOProcessor::midiInputNode));
    midiOutputNode = mainProcessor->addNode(new AudioGraphIOProcessor(AudioGraphIOProcessor::midiOutputNode));
    
    connectAudioNodes();
    connectMidiNodes();
}

void TomSirenAudioProcessor::connectAudioNodes()
{
    lfoNode = mainProcessor->addNode(new LFO());
    
    parameters.addParameterListener("lfo_freq", static_cast<LFO*>(lfoNode->getProcessor()));
    
    for (int channel = 0; channel < 2; channel++)
    {
        mainProcessor->addConnection({ { lfoNode->nodeID, channel },
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
    
//    for (auto node : mainProcessor->getNodes()) {
//        node->getProcessor()->enableAllBuses();
//    }
}

//==============================================================================
bool TomSirenAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TomSirenAudioProcessor::createEditor()
{
    return new TomSirenAudioProcessorEditor (*this, parameters);
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
