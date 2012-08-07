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

#ifndef hpp_DockPanel_hpp
#define hpp_DockPanel_hpp

// Juce related definitions go here
#include "../../../JuceLibraryCode/JuceHeader.h"
//We need DockManager
#include "DockManager.hpp"

namespace GUI 
{
    class DockPanel : public DockHolder
    {
        //Members
    private:
        friend class DockManager;
        friend class DockHolder;
        Component * content;

        //Methods
    public:
        // Component interface
        /** This resize and set components on screen */
        void resized ();
        /** This paints graphical components */
        void paint (Graphics & g);;

        //Constructor & Destructor
    public:
        /** Constructor 
            @param[in]  parent      Dock manager to manage the Panel
            @param[in]  content     Component
            @param      position    the Position whether Right/left/centre
        */
        DockPanel (DockManager * parent,Component * content,  const int position);
        /** Destructor */
        ~DockPanel ();

    };
}
#endif  // hpp_DockPanel_hpp
