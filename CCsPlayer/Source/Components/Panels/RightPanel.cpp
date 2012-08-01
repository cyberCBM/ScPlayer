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

//We need our basic class deffinitions 
#include "RightPanel.hpp"

GUI::RightPanel::RightPanel () : busyWheel(0) , playListComponent(nullptr), firstCall(true)
{
    busyWheel = new BusyWheel(BusyWheel::UZIGradient);
    addAndMakeVisible(playListComponent = new PlayListComponent());
    addAndMakeVisible(busyWheel);
    busyWheel->setVisible(false);
}
GUI::RightPanel::~RightPanel ()
{
    deleteAndZero(busyWheel);
    removeChildComponent(playListComponent);
    deleteAllChildren();
}
void GUI::RightPanel::resized ()
{
    busyWheel->setBounds(5, 5, 50, 50);
    playListComponent->setBounds(0, 0, getWidth(), getHeight());
}
void GUI::RightPanel::paint (Graphics & g)
{
      g.fillAll (Colour (0xff292929));
}

void GUI::RightPanel::activeBusyWheel()
{
    if(!busyWheel->isVisible())
    {
        busyWheel->setVisible(true);
        busyWheel->repaint();
    }
    else
        busyWheel->setVisible(false);
}

GUI::PlayListComponent * GUI::RightPanel::getPlayListComponent()
{
    return playListComponent;
}