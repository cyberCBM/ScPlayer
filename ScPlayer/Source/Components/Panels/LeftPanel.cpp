/*                                                                                  
*=====================================================================================
*ScPlayer - Server Client Player                                                                   |
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

//We need our basic class definitions 
#include "LeftPanel.hpp"

GUI::LeftPanel::LeftPanel () : clientListComponent(0)
{
	addAndMakeVisible(clientListComponent = new ClientListComponent());
}
GUI::LeftPanel::~LeftPanel ()
{
    removeChildComponent(clientListComponent);
}
void GUI::LeftPanel::resized ()
{
	clientListComponent->setBounds(0, 0, getWidth(), getHeight());
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
