/*
    This file was auto-generated!
    It contains the basic outline for a simple desktop window.
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
    centreWithSize (600, 300);
    setVisible(true);
}

GUI::MainAppWindow::~MainAppWindow()
{

}

void GUI::MainAppWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}

//int GUI::MainAppWindow::getDesktopWindowStyleFlags() const
//{
//	return getDesktopWindowStyleFlags() - ComponentPeer::windowAppearsOnTaskbar; 
//}
