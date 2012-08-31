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

#ifndef hpp_MainWindow_hpp
#define hpp_MainWindow_hpp

// Juce related definitions go here
#include "../../JuceLibraryCode/JuceHeader.h"
// custom LoolAndFeel
#include "../Common/CsLookAndFeel.hpp"

namespace GUI
{
    class TaskbarComponent;
    /** This is the main window class for CsPlayer application */
    class MainAppWindow   : public DocumentWindow
    {
        // Member Variables
    private:
        ScopedPointer<TaskbarComponent> taskbarComponent;
        /** We need tool tips throughout the window */
        TooltipWindow tooltipWindow;
        
        // Methods
    public:
        // DocumentWindow interface 
        /** When close button pressed of mainWindow (Application hide) */
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

    /** Just add a simple icon to the Window system tray area.. */
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
        /** When mouse down */
        void mouseDown (const MouseEvent & e);
        /** When mouse up */
        void mouseDoubleClick (const MouseEvent & e);

        // Constructor
    public:
        /** Constructor
            @param[in]  mainAppWindow   This is main Window holding CsPlayer */
        TaskbarComponent(MainAppWindow * mainAppWindow);
        ~TaskbarComponent() ;
    private:
        // (prevent copy constructor and operator= being generated..)
        TaskbarComponent (const TaskbarComponent&);
        const TaskbarComponent& operator= (const TaskbarComponent&);
    };
}

#endif  // hpp_MainWindow_hpp
