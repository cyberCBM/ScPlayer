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

//We need our Basic class definitions
#include "CenterPanel.hpp"

GUI::CenterPanel::CenterPanel (AudioDeviceManager & audioDeviceManager, drow::AudioFilePlayerExt & audioFilePlayer): firstCall(true)
{
    
}
GUI::CenterPanel::~CenterPanel ()
{
    deleteAllChildren();
}
void GUI::CenterPanel::resized ()
{
    if(firstCall)
    {
        firstCall = false;
    }
}
void GUI::CenterPanel::paint (Graphics & g)
{
    g.fillAll (Colours::black);
}
