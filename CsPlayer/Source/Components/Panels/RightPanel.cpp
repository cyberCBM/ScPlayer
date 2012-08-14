/*                                                                                  
*=====================================================================================
*ScPlayer - Server-Client Player ()													 |
*Music file player that plays Network stored songs                                   |
*Author: ScTeam                                                                      |
*Email: cyber.cbm@gmail.com                                                          |
*Github: https://github.com/cyberCBM/ScPlayer.git                                    |
*License: GNU2 License, Copyright (c) 2012 by ScTeam                                 |
* ScPlayer can be redistributed and/or modified under the terms of the GNU General   |
* Public License (Version 2).                                                        |
*It use JUCE and DrowAudio Libraries which holds GNU2                                |
*A copy of the license is included in the ScPlayer distribution, or can be found     |
* online at www.gnu.org/licenses.                                                    |
*=====================================================================================
*/

//We need our basic class deffinitions 
#include "RightPanel.hpp"

GUI::RightPanel::RightPanel () : playListComponent(nullptr)
{
    addAndMakeVisible(playListComponent = new PlayListComponent());
}
GUI::RightPanel::~RightPanel ()
{
    removeChildComponent(playListComponent);
    deleteAllChildren();
}
void GUI::RightPanel::resized ()
{
    playListComponent->setBounds(0, 0, getWidth(), getHeight());
}
void GUI::RightPanel::paint (Graphics & g)
{
      g.fillAll (Colour (0xff292929));
}

GUI::PlayListComponent * GUI::RightPanel::getPlayListComponent()
{
    return playListComponent;
}