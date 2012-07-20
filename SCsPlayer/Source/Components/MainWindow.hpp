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
#include "../Common/CsLookAndFeel.hpp"

namespace GUI
{
    class TaskbarComponent;

    class MainAppWindow   : public DocumentWindow
    {
        // Member Variables
    private:
        ScopedPointer<TaskbarComponent> taskbarComponent;
        
        // methods
    public:
        void closeButtonPressed();

        //void minimiseButtonPressed();

        //int getDesktopWindowStyleFlags() const;
        
    public:
        MainAppWindow();
        ~MainAppWindow();
    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainAppWindow)
    };

    // Just add a simple icon to the Window system tray area..
    class TaskbarComponent  : public SystemTrayIconComponent
    {
    private:
        MainAppWindow * mainAppWindow;

    public:
        void mouseDown (const MouseEvent & e);
        void mouseDoubleClick (const MouseEvent & e);

        // Constructor
    public:
        TaskbarComponent(MainAppWindow * mainAppWindow);
    };
}

#endif  // hpp_MainWindow_hpp
