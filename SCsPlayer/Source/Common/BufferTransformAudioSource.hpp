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

#ifndef _hpp_BufferTransformAudioSource_hpp_
#define _hpp_BufferTransformAudioSource_hpp_

// Juce related definitions go here
#include "../../JuceLibraryCode/JuceHeader.h"
namespace Configurations
{
    class BufferTransformAudioSource :  public AudioSource
    {
        // Members
    private:
        OptionalScopedPointer<AudioSource> source;
        CriticalSection lock;
        drow::Buffer buffer;

        // Methods
    public:

        /** Returns all of the settings.     */
        drow::Buffer & getBuffer()     {   return buffer;    }
        // AudioSource interface
        /** @internal. */
        void prepareToPlay (int samplesPerBlockExpected, double sampleRate);
        /** @internal. */
        void releaseResources();
        /** @internal. */
        void getNextAudioBlock (const AudioSourceChannelInfo& info);

    public:
        /** Destructor. */
        BufferTransformAudioSource (AudioSource * source, bool deleteSourceWhenDeleted = false);
        /** Destructor. */
        ~BufferTransformAudioSource();
        // (prevent copy constructor and operator= being generated..)
    private:
        BufferTransformAudioSource (const BufferTransformAudioSource&);
        const BufferTransformAudioSource& operator= (const BufferTransformAudioSource&);
    };
}
#endif // _hpp_BufferTransformAudioSource_hpp_