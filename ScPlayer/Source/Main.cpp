/*                                                                                  
*=====================================================================================
*ScPlayer - Server Client Player                                                     |
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

// Juce related definitions go here
#include "../JuceLibraryCode/JuceHeader.h"
// We need mainWindow that start Application
#include "Components/MainWindow.hpp"
// if we require the memory checker
//#include <vld.h>

/** This is the main CsPlayer class that initialize the application Inherits JUCEApplication */
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
    // Do your application's shutdown code here..
    void shutdown()    {        appWindow = 0;    }
    // When system generates quit.
    void systemRequestedQuit()    {        quit();    }
    // Returns application's name
    const String getApplicationName() { return "ScPlayer-Server";  }
    // Return Application's current version
    const String getApplicationVersion() { return ProjectInfo::versionString; }
    // TO allow more instances or not ? // Here Only one instance we will allow
    bool moreThanOneInstanceAllowed() { return false; }
    // Weather another instance of same is started On this OS ?
    void anotherInstanceStarted (const String& commandLine) {   }

private:
    ScopedPointer <GUI::MainAppWindow> appWindow;
};

// This macro generates the main() routine that starts the app.
START_JUCE_APPLICATION(CsPlayerApplication)
