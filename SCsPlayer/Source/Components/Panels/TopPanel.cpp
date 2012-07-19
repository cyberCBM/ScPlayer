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
#include "TopPanel.hpp"

GUI::TopPanel::TopPanel (AudioDeviceManager & audioDeviceManager, drow::AudioFilePlayerExt & audioFilePlayer) : 
controlBarComponent(nullptr)
{
    addAndMakeVisible( controlBarComponent = new ControlBarComponent(audioDeviceManager));
}

GUI::TopPanel::~TopPanel ()
{
    removeChildComponent(controlBarComponent);
}
void GUI::TopPanel::resized ()
{
    controlBarComponent->setBounds(0, 0, getWidth(), getHeight());
}
void GUI::TopPanel::paint (Graphics & g)
{
    // backGround Filling
    //g.fillAll (Colour (0xff292929));
    g.fillAll (Colours::white);
}
