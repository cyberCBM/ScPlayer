/*                                                                                  
*=====================================================================================
*CsPlayer - Simple Player (later It will be Server Player)                           |
*Music file player that works in Network                                             |
*Author: CsTeam                                                                      |
*Email: chaitanya.modi@gmail.com                                                     |
*Github: https://github.com/cyberCBM/CsPlayer.git                                    |
*                                                                                    |
*License: GNU2 License, Copyright (c) 2012 by CsTeam                                 |
* CsPlayer can be redistributed and/or modified under the terms of the GNU General   |
* Public License (Version 2).                                                        |
*It use JUCE and DrowAudio Libraries which holds GNU2                                |
*A copy of the license is included in the CsPlayer distribution, or can be found     |
* online at www.gnu.org/licenses.                                                    |
*=====================================================================================
*/

#include "BufferTransformAudioSource.hpp"

Configurations::BufferTransformAudioSource::BufferTransformAudioSource (AudioSource* source_,
                                                        bool deleteSourceWhenDeleted)
    : source (source_, deleteSourceWhenDeleted),
      buffer (512)
{
    jassert (source_ != nullptr);
    
    const float xScale = 1.0f / (buffer.getSize() - 1);
    
    for (int i = 0; i < buffer.getSize(); ++i)
    {
        buffer.getReference (i) = i * xScale;
    }
}

Configurations::BufferTransformAudioSource::~BufferTransformAudioSource()
{
}

void Configurations::BufferTransformAudioSource::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    source->prepareToPlay (samplesPerBlockExpected, sampleRate);
}

void Configurations::BufferTransformAudioSource::releaseResources()
{
    source->releaseResources();
}

void Configurations::BufferTransformAudioSource::getNextAudioBlock (const AudioSourceChannelInfo& info)
{
    source->getNextAudioBlock (info);
    
    const int bufferSize = buffer.getSize();
    float** channelData = info.buffer->getArrayOfChannels();
    float sample;

    for (int c = 0; c < info.buffer->getNumChannels(); ++c)
    {
        for (int s = 0; s < info.numSamples; ++s)
        {
            sample = channelData[c][s];
            
            if (sample < 0.0f && sample > -1.0f)
            {
                sample *= -1.0f;
                sample = drow::linearInterpolate (buffer.getData(), bufferSize, sample * bufferSize);
                sample *= -1.0f;
            }
            else if (sample > 0.0f && sample < 1.0f)
            {
                sample = drow::linearInterpolate (buffer.getData(), bufferSize, sample * bufferSize);
            }
            
            channelData[c][s] = sample;
        }
    }
}
