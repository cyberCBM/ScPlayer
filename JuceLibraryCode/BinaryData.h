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

// Juce related definitions go here
#include "JuceHeader.h"

namespace BinaryData
{
    extern const char*   about_gif;
    const int            about_gifSize = 1776;

    extern const char*   back_gif;
    const int            back_gifSize = 1874;

    extern const char*   icon_gif;
    const int            icon_gifSize = 2038;

    extern const char*   open_gif;
    const int            open_gifSize = 2084;

    extern const char*   pause_gif;
    const int            pause_gifSize = 1865;

    extern const char*   play_gif;
    const int            play_gifSize = 1822;

    extern const char*   setup_gif;
    const int            setup_gifSize = 1843;

    extern const char*   stop_gif;
    const int            stop_gifSize = 1745;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();

    //==============================================================================
    // This class acts as an ImageProvider that will access the BinaryData images
    class ImageProvider  : public juce::ComponentBuilder::ImageProvider
    {
    public:
        ImageProvider() noexcept {}

        juce::Image getImageForIdentifier (const juce::var& imageIdentifier)
        {
            int dataSize = 0;
            const char* const data = getNamedResource (imageIdentifier.toString().toUTF8(), dataSize);

            if (data != nullptr)
                return juce::ImageCache::getFromMemory (data, dataSize);

            return juce::Image();
        }

        juce::var getIdentifierForImage (const juce::Image&)  { return juce::var(); }
    };

}

