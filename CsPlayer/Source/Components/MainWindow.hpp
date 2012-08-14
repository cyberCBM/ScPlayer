/*                                                                                  
*=====================================================================================
*ScPlayer - Server-Client Player ()													 |
*Music file player that plays Network stored songs                                   |
*Author: ScTeam                                                                      |
*Email: cyber.cbm@gmail.com                                                          |
*Github: https://github.com/cyberCBM/ScPlayer.git                                    |*License: GNU2 License, Copyright (c) 2012 by ScTeam                                 |
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
// We need ClientSettingComponent
#include "../Components/PanelComponent/ClientSettingComponent.hpp"

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
        
    public:
        MainAppWindow();
        ~MainAppWindow();
    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainAppWindow)
    };

    ///////////////////////////////////////////////////////////////////////////////

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

    class clientSettingDialogWindow : public DialogWindow
    {
    public:
        clientSettingDialogWindow (GUI::ClientSettingComponent * clientSettingComp)
            : DialogWindow ("Client Settings", Colours::darkgrey, true, true), clientSettingComp(clientSettingComp)
        {
            setContentOwned (clientSettingComp, true);
            centreWithSize(330, 250);
            setResizable (false, false);
        }

        ~clientSettingDialogWindow()
        {
            removeChildComponent(clientSettingComp);
        }

        void closeButtonPressed()
        {
            if(clientSettingComp)
            {
                if(clientSettingComp->isConnectClient())
                {
                    JUCEApplication::getInstance()->systemRequestedQuit();
                }
                else
                {
                    clientSettingComp->writeToXML();
                    setVisible(false);
                    exitModalState(1);
                }
            }
            else
                setVisible (true);
        }

    private:
        ScopedPointer<GUI::ClientSettingComponent>  clientSettingComp;

    private:
        JUCE_DECLARE_NON_COPYABLE (clientSettingDialogWindow);
    };
}

#endif  // hpp_MainWindow_hpp
