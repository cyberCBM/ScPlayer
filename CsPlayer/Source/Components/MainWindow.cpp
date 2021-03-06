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
*A copy of the license is included in the ScPlayer distribution, or can be found     |
* online at www.gnu.org/licenses.                                                    |
*=====================================================================================
*/

// We need our basic definitions
#include "MainWindow.hpp"
// We need Component in Main Window
#include "MainComponent.hpp"
// We need ClientSettingComponent
#include "../Components/PanelComponent/ClientSettingComponent.hpp"

GUI::MainAppWindow::MainAppWindow() : 
    DocumentWindow (JUCEApplication::getInstance()->getApplicationName(),
    Colours::darkgrey,
    DocumentWindow::minimiseButton | DocumentWindow::closeButton,
    true)
{
    GUI::MainComponent * const contentComponent = new MainComponent ();
    setContentOwned (contentComponent, false);
    // don't want the window to take focus when the title-bar is clicked..
    setWantsKeyboardFocus(true);
    setIcon(ImageCache::getFromMemory(BinaryData::icon_gif, BinaryData::icon_gifSize));
    setTitleBarTextCentred(false);
    //setResizable(false, false); // Will Deicide later for doing resizing in it.
    setResizable(false, false);
    setResizeLimits(330, 600, 330, 600);
    // Making size settings
    // centreWithSize (600, 300); // Server Setting
    centreWithSize (330, 600);
    setVisible(true);
    // Create system tray Icon for this player
    #if JUCE_WINDOWS || JUCE_LINUX
    taskbarComponent = new TaskbarComponent(this);
   #endif
}

GUI::MainAppWindow::~MainAppWindow()
{
    removeChildComponent(taskbarComponent);
}

void GUI::MainAppWindow::closeButtonPressed()
{
    //JUCEApplication::getInstance()->systemRequestedQuit();
    setVisible(false);
}

////////////////////////////////////////////////////////////////////////////////////

GUI::TaskbarComponent::TaskbarComponent(MainAppWindow * mainAppWindow) : mainAppWindow(mainAppWindow)
{
    setIconImage (ImageCache::getFromMemory(BinaryData::icon_gif, BinaryData::icon_gifSize));
    setIconTooltip ("ScPlayer Client");
}

GUI::TaskbarComponent::~TaskbarComponent() 
{
}

void GUI::TaskbarComponent::mouseDown (const MouseEvent & e)
{
    if(e.mods.isRightButtonDown())
    {
        PopupMenu popMenu;
        // these are temporary lookandfeel settings
        LookAndFeel::getDefaultLookAndFeel().setColour(PopupMenu::backgroundColourId, Colour (0xff292929));
        LookAndFeel::getDefaultLookAndFeel().setColour(PopupMenu::textColourId, Colours::black);
        LookAndFeel::getDefaultLookAndFeel().setColour(PopupMenu::highlightedBackgroundColourId, Colours::grey);
        LookAndFeel::getDefaultLookAndFeel().setColour(PopupMenu::highlightedTextColourId, Colours::white);
        popMenu.addItem (1, "CsPlayer");
        popMenu.addItem (2, "Quit Player");
        const int result = popMenu.show();
        if (result == 1)
        {
            if(!mainAppWindow->isVisible())
                mainAppWindow->setVisible(true);
            else
                mainAppWindow->setMinimised(false);
        }
        else if(result == 2)
            JUCEApplication::getInstance()->systemRequestedQuit();
    }
}

void GUI::TaskbarComponent::mouseDoubleClick (const MouseEvent & e)
{
    if(e.mods.isLeftButtonDown())
    {
        if(!mainAppWindow->isVisible())
            mainAppWindow->setVisible(true);
    }
}