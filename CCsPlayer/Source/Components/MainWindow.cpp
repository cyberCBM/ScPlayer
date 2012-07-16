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

// We need our basic definitions
#include "MainWindow.hpp"
// We need Component in Main Window
#include "MainComponent.hpp"

GUI::MainAppWindow::MainAppWindow() : 
    DocumentWindow (JUCEApplication::getInstance()->getApplicationName(),
    Colours::darkgrey,
    DocumentWindow::minimiseButton | DocumentWindow::closeButton,
    true)
{
    GUI::MainComponent::applyTranslation(String::empty);

    GUI::MainComponent * const contentComponent = new MainComponent ();
    
    // don't want the window to take focus when the title-bar is clicked..
    setWantsKeyboardFocus(true);
    setIcon(ImageCache::getFromMemory(BinaryData::icon_gif, BinaryData::icon_gifSize));
    setTitleBarTextCentred(false);
    //setResizable(false, false); // Will Deicide later for doing resizing in it.
    setContentOwned (contentComponent, false);
    centreWithSize (330, 500);
    setVisible(true);
}

GUI::MainAppWindow::~MainAppWindow()
{

}

void GUI::MainAppWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}

