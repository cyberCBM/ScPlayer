/*
  ==============================================================================
  
  This file is part of the dRowAudio JUCE module
  Copyright 2004-12 by dRowAudio.
  
  ------------------------------------------------------------------------------
 
  dRowAudio can be redistributed and/or modified under the terms of the GNU General
  Public License (Version 2), as published by the Free Software Foundation.
  A copy of the license is included in the module distribution, or can be found
  online at www.gnu.org/licenses.
  
  dRowAudio is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
  
  ==============================================================================
*/

#if DROWAUDIO_USE_SOUNDTOUCH

using namespace soundtouch;

SoundTouchProcessor::SoundTouchProcessor()
    : interleavedInputBufferSize (512),
      interleavedOutputBufferSize (512)
{
    setPlaybackSettings (settings);
    
    interleavedInputBuffer.malloc (interleavedInputBufferSize * 2);
    interleavedOutputBuffer.malloc (interleavedOutputBufferSize * 2);
}

SoundTouchProcessor::~SoundTouchProcessor()
{
}

void SoundTouchProcessor::initialise (int numChannels, double sampleRate)
{
    ScopedLock sl (lock);
    soundTouch.setChannels (numChannels);
    soundTouch.setSampleRate ((uint32) sampleRate);
    soundTouch.clear();
}

void SoundTouchProcessor::writeSamples (float** sourceChannelData, int numChannels, int numSamples, int startSampleOffset)
{
    const int requiredBufferSize = numSamples * numChannels;
    if (interleavedInputBufferSize < requiredBufferSize) 
    {
        interleavedInputBuffer.malloc (requiredBufferSize);
        interleavedInputBufferSize = requiredBufferSize;
    }
    
    for (int i = 0; i < numChannels; i++)
        sourceChannelData[i] += startSampleOffset;
    
    AudioDataConverters::interleaveSamples ((const float**) sourceChannelData, interleavedInputBuffer,                                        
                                            numSamples, numChannels);
    
    for (int i = 0; i < numChannels; i++)
        sourceChannelData[i] -= startSampleOffset;
    
    ScopedLock sl (lock);
    soundTouch.putSamples ((SAMPLETYPE*) interleavedInputBuffer, numSamples);
}

void SoundTouchProcessor::readSamples (float** destinationChannelData, int numChannels, int numSamples, int startSampleOffset)
{
    const int requiredBufferSize = numSamples * numChannels;
    if (interleavedOutputBufferSize < requiredBufferSize) 
    {
        interleavedOutputBuffer.malloc (requiredBufferSize);
        interleavedOutputBufferSize = requiredBufferSize;
    }
    
    int numSamplesDone = 0;
    int numThisTime = 0;
    
    {
        ScopedLock sl (lock);
    
        do
        {
            int maxNumSamples = numSamples - numSamplesDone;
            numThisTime = soundTouch.receiveSamples ((SAMPLETYPE*) &interleavedOutputBuffer[numChannels * numSamplesDone], maxNumSamples);
            
            numSamplesDone += numThisTime;
            
            if (numSamplesDone == numSamples)
                break;
        }
        while (numThisTime != 0);
    }
    
    if (numSamplesDone < numSamples)
        zeromem (&interleavedOutputBuffer[numChannels * numSamplesDone], numChannels * sizeof (numSamples - numSamplesDone));
    
    for (int i = 0; i < numChannels; i++)
        destinationChannelData[i] += startSampleOffset;
    
    AudioDataConverters::deinterleaveSamples (interleavedOutputBuffer, destinationChannelData,                                        
                                              numSamples, numChannels);
    for (int i = 0; i < numChannels; i++)
        destinationChannelData[i] -= startSampleOffset;
}

void SoundTouchProcessor::setPlaybackSettings (PlaybackSettings newSettings)
{
    settings = newSettings;
    
    ScopedLock sl (lock);
    soundTouch.setRate (settings.rate);
    soundTouch.setTempo (settings.tempo);
    soundTouch.setPitch (settings.pitch);    
}


void SoundTouchProcessor::setSoundTouchSetting (int settingId, int settingValue)
{
    soundTouch.setSetting (settingId, settingValue);
}

int SoundTouchProcessor::getSoundTouchSetting (int settingId)
{
    return soundTouch.getSetting (settingId);
}


#endif