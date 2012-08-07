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

// We need our basic class definitions
#include "MainComponent.hpp"
// We need mainWindow
#include "MainWindow.hpp"

GUI::MainComponent::MainComponent () : 
firstCall(true), manager(nullptr)
{
    addAndMakeVisible (manager = new DockManager());
    // left
    leftPanel = new LeftPanel();
    manager->setPanelComponent (LEFT, leftPanel);
    //right
    rightPanel = new RightPanel();
    manager->setPanelComponent (RIGHT,  rightPanel);
    
}
GUI::MainComponent::~MainComponent ()
{
    removeChildComponent(manager);
    removeChildComponent(rightPanel);
    removeChildComponent(leftPanel);
    deleteAllChildren ();
}
void GUI::MainComponent::resized ()
{
    setSize(330, 600);
    if(manager)
        manager->setBounds (0, 0, getWidth(), getHeight());
}

GUI::RightPanel * GUI::MainComponent::getRightPanel()
{
    return rightPanel;
}

GUI::LeftPanel * GUI::MainComponent::getLeftPanel()
{
    return leftPanel;
}