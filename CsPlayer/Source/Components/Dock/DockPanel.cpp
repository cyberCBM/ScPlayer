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

//We need our basics class definitions 
#include "DockPanel.hpp"
//We need dock button's definitions 
#include "DockButtons.hpp"

GUI::DockPanel::DockPanel (DockManager * parent, Component * component, const int position)
:DockHolder (parent, this, position), content(component)
{
    content->addMouseListener (this, true);
    addAndMakeVisible (content);
}

GUI::DockPanel::~DockPanel ()
{
    deleteAllChildren ();
}

void GUI::DockPanel::resized ()
{
    content->setBounds (DockHolder::getContentBounds());
    DockHolder::resized ();
}
void GUI::DockPanel::paint (Graphics & g)
{
    DockHolder::paint (g);
}