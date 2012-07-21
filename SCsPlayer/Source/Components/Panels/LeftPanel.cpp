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

GUI::LeftPanel::LeftPanel () : clientListComponent(0)
{
	addAndMakeVisible(clientListComponent = new ClientListComponent());
}
GUI::LeftPanel::~LeftPanel ()
{
	deleteAndZero(clientListComponent);
}
void GUI::LeftPanel::resized ()
{
	clientListComponent->setBounds(2, 15, getWidth() - 4, getHeight()-17);
}
void GUI::LeftPanel::paint (Graphics & g)
{
    // backGround Filling
    g.fillAll (Colour (0xff292929));
}

GUI::ClientListComponent * GUI::LeftPanel::getClientListComponent()
{
    return clientListComponent;
}
