/*                                                                                  
*=====================================================================================
*ScPlayer - Server Client Player                                                                   |
*Music file player that works in Network                                             |
*Author: ScTeam                                                                      |
*Email: cyber.cbm@gmail.com															 |
*Github: https://github.com/cyberCBM/ScPlayer.git                                    |
*                                                                                    |
*License: GNU2 License, Copyright (c) 2012 by ScTeam                                 |
* ScPlayer can be redistributed and/or modified under the terms of the GNU General   |
* Public License (Version 2).                                                        |
*It use JUCE and DrowAudio Libraries which holds GNU2                                |
*A copy of the license is included in the ScPlayer distribution, or can be found     |
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
        /** Returns PlayerComponent to controller 
            Which is used to communicate around player's data and command */
        PlayerComponent * getPlayerComponent();

        // Constructor & Destructor
    public:
        /** Constructor 
            @param applicationData Reference about the data of the application        */
        CenterPanel (AudioDeviceManager & audioDeviceManager, drow::AudioFilePlayerExt & audioFilePlayer);
        /** Destructor */
        ~CenterPanel ();
        // (prevent copy constructor and operator= being generated..)
    private:
        CenterPanel (const CenterPanel&);
        const CenterPanel& operator= (const CenterPanel&);
    };
}

#endif  // hpp_CenterPanel_hpp