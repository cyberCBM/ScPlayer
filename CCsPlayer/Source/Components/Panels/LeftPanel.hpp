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

#ifndef hpp_BottomPanel_hpp
#define hpp_BottomPanel_hpp

// Juce related definitions go here
#include "../../../JuceLibraryCode/JuceHeader.h"
//We need panel component
#include "../PanelComponent/ClientControlComponent.hpp"

namespace GUI 
{
    class LeftPanel : public Component
                      
    {
        // Members
    private:
         /** Boolean to initialise the class only once in resized method */
        bool firstCall;
        /** The component for the Client Control */
        ClientControlComponent *   clientControlComponent;

        // Methods
    public:
        // Component interface
        /** This resize and set components on screen */
        void resized ();
        /** This paints graphical components */
        void paint (Graphics & g);
        /** Returns PlayListComponent to controller 
            Which is used to communicate around playlist data */
        ClientControlComponent * getClientControlComponent();

        // Constructor & Destructor
    public:
        /** Constructor */
        LeftPanel ();
        /** Destructor */
        ~LeftPanel ();
    };
}
#endif //hpp_BottomPanel _hpp