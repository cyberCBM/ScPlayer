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

// Juce related definitions go here
#include "../JuceLibraryCode/JuceHeader.h"
// We need mainWindow that start Application
#include "Components/MainWindow.hpp"

//#include <vld.h>
/** This is the main CsPlayer class that initialize the application 
    Inherits JUCEApplication */
class CsPlayerApplication  : public JUCEApplication
{
public:
    CsPlayerApplication()
    {
    }

    ~CsPlayerApplication()
    {
    }
    
    void initialise (const String& commandLine)
    {
        // Do your application's initialisation code here..
        appWindow = new GUI::MainAppWindow();
    }

    void shutdown()
    {
        // Do your application's shutdown code here..
        appWindow = 0;
    }

    void systemRequestedQuit()    {        quit();    }

    const String getApplicationName() { return "CsPlayer - Server";  }

    const String getApplicationVersion() { return ProjectInfo::versionString; }

    bool moreThanOneInstanceAllowed() { return true; }

    void anotherInstanceStarted (const String& commandLine) {   }


private:
    ScopedPointer <GUI::MainAppWindow> appWindow;
};

// This macro generates the main() routine that starts the app.
START_JUCE_APPLICATION(CsPlayerApplication)
