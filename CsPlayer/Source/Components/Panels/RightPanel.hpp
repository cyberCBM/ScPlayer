/*                                                                                  
*=====================================================================================
*ScPlayer - Server-Client Player ()													 |
*Music file player that plays Network stored songs                                   |
*Author: ScTeam                                                                      |
*Email: cyber.cbm@gmail.com                                                          |
*Github: https://github.com/cyberCBM/ScPlayer.git                                    |
*License: GNU2 License, Copyright (c) 2012 by ScTeam                                 |
* ScPlayer can be redistributed and/or modified under the terms of the GNU General   |
* Public License (Version 2).                                                        |
*It use JUCE and DrowAudio Libraries which holds GNU2                                |
*A copy of the license is included in the ScPlayer distribution, or can be found     |
* online at www.gnu.org/licenses.                                                    |
*=====================================================================================
*/

#ifndef hpp_HeaderPanel_hpp
#define hpp_HeaderPanel_hpp
// Juce related definitions go here
#include "../../../JuceLibraryCode/JuceHeader.h"
// We need panel component
#include "../PanelComponent/PlayListComponent.hpp"

namespace GUI 
{
    class RightPanel : public Component
    {
        // Member
    private:
        /** PlayList Component */
        ScopedPointer<PlayListComponent>  playListComponent;

        // Methods
    public:
        // Component interface
        /** This resize and set components on screen */
        void resized ();
        /** This paints graphical components */
        void paint (Graphics & g);

        //Class Interface
        /** Returns PlayListComponent to controller 
            Which is used to communicate around playlist data */
        PlayListComponent * getPlayListComponent();

        // Constructor & Destructor
    public:
        /** Constructor */
        RightPanel ();
        /** Destructor */
        ~RightPanel ();
    };
}
#endif //hpp_HeaderPanel_hpp