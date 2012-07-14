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

#ifndef hpp_MainWindow_hpp
#define hpp_MainWindow_hpp

// Juce related definitions go here
#include "../../JuceLibraryCode/JuceHeader.h"
// custom LoolAndFeel
#include "../Common/LookAndFeel.hpp"

namespace GUI
{
    class MainAppWindow   : public DocumentWindow
    {
        // methods
    public:
        void closeButtonPressed();

        //int getDesktopWindowStyleFlags() const;
        /* Note: Be careful when overriding DocumentWindow methods - the base class
        uses a lot of them, so by overriding you might break its functionality.
        It's best to do all your work in you content component instead, but if
        you really have to override any DocumentWindow methods, make sure your
        implementation calls the superclass's method.
        */
    public:
        MainAppWindow();
        ~MainAppWindow();
    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainAppWindow)
    };
}

#endif  // hpp_MainWindow_hpp
