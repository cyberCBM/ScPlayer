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

#ifndef __DROWAUDIO_BUFFERTRANSFORMAUDIOSOURCE_H__
#define __DROWAUDIO_BUFFERTRANSFORMAUDIOSOURCE_H__

// Juce related definitions go here
#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
class BufferTransformAudioSource :  public AudioSource
{
public:
    //==============================================================================
    BufferTransformAudioSource (AudioSource * source,
                                bool deleteSourceWhenDeleted = false);
    
    /** Destructor. */
    ~BufferTransformAudioSource();
    
    /** Returns all of the settings.
     */
    drow::Buffer & getBuffer()     {   return buffer;    }
        
    //==============================================================================
    /** @internal. */
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate);
    
    /** @internal. */
    void releaseResources();
    
    /** @internal. */
    void getNextAudioBlock (const AudioSourceChannelInfo& info);
        
private:
    //==============================================================================
    OptionalScopedPointer<AudioSource> source;
    CriticalSection lock;
    drow::Buffer buffer;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BufferTransformAudioSource);
};

#endif //__DROWAUDIO_BUFFERTRANSFORMAUDIOSOURCE_H__