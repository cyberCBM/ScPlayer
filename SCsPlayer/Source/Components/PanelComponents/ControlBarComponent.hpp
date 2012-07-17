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

#ifndef hpp_ControlBarComponent_hpp
#define hpp_ControlBarComponent_hpp

// Juce related definitions go here
#include "../../../JuceLibraryCode/JuceHeader.h"

namespace GUI
{
    class ControlBarComponent : public Component
    {
        // Members
    private:
        /** Audio Device Manager that hold input and output devices */
        AudioDeviceManager & audioDeviceManager;
        // Methods
    public:
        void resized();
        void paint(Graphics & g);

        // Constructor & Destructor
    public:
        ControlBarComponent(AudioDeviceManager & audioDeviceManager);
        ~ControlBarComponent();
    }
}

#endif // hpp_ControlBarComponent_hpp