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

#ifndef hpp_HeaderPanel_hpp
#define hpp_HeaderPanel_hpp
// Juce related definitions go here
#include "../../../JuceLibraryCode/JuceHeader.h"

namespace GUI 
{
    class RightPanel : public Component
    {
        // Member
    private:

        // Methods
    public:
        // Component interface
        /** This resize and set components on screen */
        void resized ();
        /** This paints graphical components */
        void paint (Graphics & g);

        // Constructor & Destructor
    public:
        /** Constructor */
        RightPanel ();
        /** Destructor */
        ~RightPanel ();
    };
}
#endif //hpp_HeaderPanel_hpp