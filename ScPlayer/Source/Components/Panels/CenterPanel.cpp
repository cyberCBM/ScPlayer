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

//We need our Basic class definitions
#include "CenterPanel.hpp"

GUI::CenterPanel::CenterPanel (AudioDeviceManager & audioDeviceManager, drow::AudioFilePlayerExt & audioFilePlayer): firstCall(true), playerComponent(nullptr)
{
    addAndMakeVisible(playerComponent = new PlayerComponent(audioDeviceManager, audioFilePlayer));
}

GUI::CenterPanel::~CenterPanel ()
{
    removeChildComponent (playerComponent);
}

void GUI::CenterPanel::resized ()
{
    if(firstCall)
    {
        firstCall = false;
    }
    playerComponent->setBounds(0, 0, getWidth(), getHeight());
}

void GUI::CenterPanel::paint (Graphics & g)
{
    // backGround Filling
    g.fillAll (Colour (0xff292929));
}

GUI::PlayerComponent * GUI::CenterPanel::getPlayerComponent()
{
    if(playerComponent)
        return playerComponent;
    else 
        return 0;
}
