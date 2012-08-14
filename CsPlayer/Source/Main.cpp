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
*A copy of the license is included in the CsPlayer distribution, or can be found     |
* online at www.gnu.org/licenses.                                                    |
*=====================================================================================
*/

// Juce related definitions go here
#include "../JuceLibraryCode/JuceHeader.h"
// We need mainWindow that start Application
#include "Components/MainWindow.hpp"

/** This is the main CsPlayer class that initialize the application 
    Inherits JUCEApplication */
class CsPlayerApplication  : public JUCEApplication
{
    /** Constructor & destructor */
public:
    CsPlayerApplication()
    {
    }

    ~CsPlayerApplication()
    {
    }
    // This is the first method that is called after main in created for CsPlayerApplication
    void initialise (const String& commandLine)
    {
        XmlDocument mainDoc(File(File::getCurrentWorkingDirectory().getFullPathName() + File::separatorString + "csProp.xml"));
        mainElement = mainDoc.getDocumentElement();
        if(mainElement == 0)
        {
            Logger::outputDebugString("No Cs Setting file avaialble");
            GUI::clientSettingDialogWindow clientSettingWindow(new GUI::ClientSettingComponent(true));
            clientSettingWindow.runModalLoop();
        }
        File check(File::getCurrentWorkingDirectory().getFullPathName() + File::separatorString + "csProp.xml");
        if(check.exists())
            appWindow = new GUI::MainAppWindow(); // Do your application's initialisation code here..
    }
    // Do your application's shutdown code here..
    void shutdown()    {    appWindow = 0;    }
    // This quit the csPlayer application
    void systemRequestedQuit()    {        quit();    }
    // Returns application's name
    const String getApplicationName() { return "ScPlayer-Client";  }
    // Return Application's current version
    const String getApplicationVersion() { return ProjectInfo::versionString; }
    // TO allow more instances or not ? // Here Only one instance we will allow
    bool moreThanOneInstanceAllowed() { return false; }
    // Weather another instance of same is started On this OS ?
    void anotherInstanceStarted (const String& commandLine) {   }

private:
    /** Application's main window(document window is created here) */
    ScopedPointer <GUI::MainAppWindow> appWindow;
    /** To read xml related thigs to show either application window or connect dialog window */
    ScopedPointer <XmlElement> mainElement;
};

// This macro generates the main() routine that starts the app.
START_JUCE_APPLICATION(CsPlayerApplication)
