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

//We need our basic class definitions 
#include "LeftPanel.hpp"

GUI::LeftPanel::LeftPanel () : clientControlComponent(0), firstCall(true)
{
    addAndMakeVisible(clientControlComponent = new ClientControlComponent());
}
GUI::LeftPanel::~LeftPanel ()
{
    deleteAndZero(clientControlComponent);
    deleteAllChildren();
}
void GUI::LeftPanel::resized ()
{
    if(firstCall)
    {
        firstCall = false;
    }
    clientControlComponent->setBounds(0, 0, getWidth(), getHeight());
}
void GUI::LeftPanel::paint (Graphics & g)
{
      g.fillAll (Colour (0xff292929));
}

GUI::ClientControlComponent * GUI::LeftPanel::getClientControlComponent()
{
    return clientControlComponent;
}