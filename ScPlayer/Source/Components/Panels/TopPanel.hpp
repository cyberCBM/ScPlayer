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

#ifndef hpp_TopPanel_hpp
#define hpp_TopPanel_hpp

// Juce related definitions go here
#include "../../../JuceLibraryCode/JuceHeader.h"
// We need ControlBarComponent as component inside TOP
#include "../PanelComponents/ControlBarComponent.hpp"

namespace GUI 
{
    class TopPanel : public Component
    {
        // Members
    private:
        /** Control Bar which set audio device, show main menu icons, 
            start and stop server, enable and disable clients */
        ScopedPointer<ControlBarComponent> controlBarComponent;
        // Methods
    public:
        // Component interface
        /** This resize and set components on screen */
        void resized ();
        /** This paints graphical components */
        void paint (Graphics & g);
        /** Get controlBar component */    
        ControlBarComponent * getControlBarComponent();

        // Constructor & Destructor
    public:
        /** Constructor 
            @param[in-out] audioDeviceManager   Device manager holding audio device on which music is being played
            @param[in-out] audioFilePlayer      Audio Player's actual implementation which do play files */
        TopPanel (AudioDeviceManager & audioDeviceManager, drow::AudioFilePlayerExt & audioFilePlayer);
        /** Destructor */
        ~TopPanel ();
        // (prevent copy constructor and operator= being generated..)
    private:
        TopPanel (const TopPanel&);
        const TopPanel& operator= (const TopPanel&);
    };
}
#endif //hpp_TopPanel _hpp