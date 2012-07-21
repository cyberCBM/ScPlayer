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

#ifndef hpp_CenterPanel_hpp
#define hpp_CenterPanel_hpp

// Juce related definitions go here
#include "../../../JuceLibraryCode/JuceHeader.h"
// We need the player component
#include "../PanelComponents/PlayerComponent.hpp"

namespace GUI 
{
    class CenterPanel : public Component
    {
        // Members
    private:
        /** Boolean to initialise the class only once in resized method */
        bool                                firstCall;
        /** The component for the player */
        ScopedPointer<PlayerComponent>      playerComponent;

        // Methods
    public:
        // Component interface
        /** This resize and set components on screen */
        void resized ();
        /** This paints graphical components */
        void paint (Graphics & g);

        PlayerComponent * getPlayerComponent();

        // Constructor & Destructor
    public:
        /** Constructor 
            @param applicationData Reference about the data of the application        */
        CenterPanel (AudioDeviceManager & audioDeviceManager, drow::AudioFilePlayerExt & audioFilePlayer);
        /** Destructor */
        ~CenterPanel ();
    };
}

#endif  // hpp_CenterPanel_hpp