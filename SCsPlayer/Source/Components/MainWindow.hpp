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
        // We need tool tips throughout the window
        TooltipWindow tooltipWindow;
        
        // Methods
    public:
        // DocumentWindow interface 
        void closeButtonPressed();
        
        // Constructor & Destructor
    public:
        /** Constructor */
        MainAppWindow();
        /** Destructor*/
        ~MainAppWindow();
        // (prevent copy constructor and operator= being generated..)
    private:
        MainAppWindow (const MainAppWindow&);
        const MainAppWindow& operator= (const TaskbarComponent&);
    };

    // Just add a simple icon to the Window system tray area..
    class TaskbarComponent  : public SystemTrayIconComponent
    {
    private:
        /** Main application window that is used to
            hide the app when called from tray - Hide 
            Show the app when called from tray - Show
            Quit the app when called from tray - Quit */
        MainAppWindow * mainAppWindow;

    public:
        // Component interface
        void mouseDown (const MouseEvent & e);
        void mouseDoubleClick (const MouseEvent & e);

        // Constructor
    public:
        TaskbarComponent(MainAppWindow * mainAppWindow);
    private:
        // (prevent copy constructor and operator= being generated..)
        TaskbarComponent (const TaskbarComponent&);
        const TaskbarComponent& operator= (const TaskbarComponent&);
    };
}

#endif  // hpp_MainWindow_hpp
