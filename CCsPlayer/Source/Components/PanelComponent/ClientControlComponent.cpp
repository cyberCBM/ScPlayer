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
#include "ClientControlComponent.hpp"
// AboutUs components
#include "ClientSettingComponent.hpp"
// AboutUs components
#include "AboutusComponent.hpp"
// LookAndFeel to set for scrollBar and other things
#include "../../Common/CsLookAndFeel.hpp"

#include "../MainComponent.hpp"

GUI::ClientControlComponent::ClientControlComponent (): firstCall(true), connectButton(nullptr), settingButton(nullptr),
                                                        playPauseButton(nullptr), backwardButton(nullptr),
                                                        stopButton(nullptr), forwardButton(nullptr), aboutButton(nullptr),
                                                        clockComp(nullptr), clientConnectionObject(nullptr)
{
    clientConnectionObject = new NetworkConnection::ClientConnection(*this);
    addAndMakeVisible (clockComp = new drow::Clock());

    addAndMakeVisible (connectButton = new ImageButton("connect"));
    addAndMakeVisible (settingButton = new ImageButton("setting"));
    addAndMakeVisible (playPauseButton = new ImageButton("playpause"));
    addAndMakeVisible (backwardButton = new ImageButton("backward"));
    addAndMakeVisible (stopButton = new ImageButton("stop"));
    addAndMakeVisible (forwardButton = new ImageButton("forward"));
    addAndMakeVisible (aboutButton = new ImageButton("about"));
   
    Image img1, img2;
    // connect/disconnect
    img1 = ImageCache::getFromMemory(BinaryData::startS_gif, BinaryData::startS_gifSize);
    img2 = ImageCache::getFromMemory(BinaryData::stopS_gif, BinaryData::stopS_gifSize);
    connectButton->setToggleState(false, false);
    connectButton->setImages (true, false, true, 
                                img1, 1.0f, Colours::transparentBlack,
                                img1, 0.7f, Colours::transparentBlack,
                                img2, 1.0f, Colours::transparentBlack);
    connectButton->addButtonListener (this);

    // setting
    img1 = ImageCache::getFromMemory(BinaryData::setting_gif, BinaryData::setting_gifSize);
    settingButton->setImages(true, false, true,
                            img1, 1.0f, Colours::transparentBlack,
                            img1, 0.7f, Colours::transparentBlack,
                            img1, 1.0f, Colours::transparentBlack);
    settingButton->addButtonListener (this);

    // backward
    img1 = ImageCache::getFromMemory(BinaryData::back_gif, BinaryData::back_gifSize);
    backwardButton->setImages(true, false, true,
                            img1, 1.0f, Colours::transparentBlack,
                            img1, 0.7f, Colours::transparentBlack,
                            img1, 1.0f, Colours::transparentBlack);
    backwardButton->addButtonListener (this);

    // play/pause
    img1 = ImageCache::getFromMemory(BinaryData::play_gif, BinaryData::play_gifSize);
    img2 = ImageCache::getFromMemory(BinaryData::pause_gif, BinaryData::pause_gifSize);
    playPauseButton->setToggleState(false, false);
    playPauseButton->setImages(true, false, true,
                            img1, 1.0f, Colours::transparentBlack,
                            img1, 0.7f, Colours::transparentBlack,
                            img2, 1.0f, Colours::transparentBlack);
    playPauseButton->addButtonListener (this);

    // stop
    img1 = ImageCache::getFromMemory(BinaryData::stop_gif, BinaryData::stop_gifSize);
    stopButton->setImages(true, false, true,
                            img1, 1.0f, Colours::transparentBlack,
                            img1, 0.7f, Colours::transparentBlack,
                            img1, 1.0f, Colours::transparentBlack);
    stopButton->addButtonListener (this);

    // forward
    img1 = ImageCache::getFromMemory(BinaryData::next_gif, BinaryData::next_gifSize);
    forwardButton->setImages(true, false, true,
                            img1, 1.0f, Colours::transparentBlack,
                            img1, 0.7f, Colours::transparentBlack,
                            img1, 1.0f, Colours::transparentBlack);
    forwardButton->addButtonListener (this);

    // about
    img1 = ImageCache::getFromMemory(BinaryData::about_gif, BinaryData::about_gifSize);
    aboutButton->setImages(true, false, true,
                            img1, 1.0f, Colours::transparentBlack,
                            img1, 0.7f, Colours::transparentBlack,
                            img1, 1.0f, Colours::transparentBlack);
    aboutButton->addButtonListener (this);
}
GUI::ClientControlComponent::~ClientControlComponent ()
{
    deleteAndZero(clientConnectionObject);
}
void GUI::ClientControlComponent::resized ()
{
    const int clockWidth = 80, clockHeight = 20;
    clockComp->setBounds(proportionOfWidth(0.5f) - clockWidth/2, proportionOfHeight(0.02f), clockWidth, clockHeight );

    connectButton->setBounds(proportionOfWidth(0.5f) - connectButton->getWidth()/2, proportionOfHeight(0.06f), connectButton->getWidth(), connectButton->getHeight());

    settingButton->setBounds(proportionOfWidth(0.5f) - settingButton->getWidth()/2, proportionOfHeight(0.16f), settingButton->getWidth(), settingButton->getHeight());

    backwardButton->setBounds(proportionOfWidth(0.5f) - backwardButton->getWidth()/2, proportionOfHeight(0.3f), backwardButton->getWidth(), backwardButton->getHeight());

    playPauseButton->setBounds(proportionOfWidth(0.5f) - playPauseButton->getWidth()/2, proportionOfHeight(0.4f), playPauseButton->getWidth(), playPauseButton->getHeight());

    stopButton->setBounds(proportionOfWidth(0.5f) - stopButton->getWidth()/2, proportionOfHeight(0.5f), stopButton->getWidth(), stopButton->getHeight());
    
    forwardButton->setBounds(proportionOfWidth(0.5f) - forwardButton->getWidth()/2, proportionOfHeight(0.6f), forwardButton->getWidth(), forwardButton->getHeight());

    aboutButton->setBounds(proportionOfWidth(0.5f) - aboutButton->getWidth()/2, proportionOfHeight(0.74f), aboutButton->getWidth(), aboutButton->getHeight());
}
void GUI::ClientControlComponent::paint (Graphics & g)
{
      g.fillAll (Colour (0xff292929));
}

void GUI::ClientControlComponent::buttonClicked (Button* buttonThatWasClicked)
{
    if(buttonThatWasClicked == connectButton)
    {   
        findParentComponentOfClass<GUI::MainComponent>()->getRightPanel()->activeBusyWheel();
        if(clientConnectionObject->connectToServer(false))
        {
            int k = 0;
        }
        connectButton->setToggleState(!(connectButton->getToggleState()), false);
    }
    else if(buttonThatWasClicked == settingButton)
    {
        setConfiguration();        
    }
    else if(buttonThatWasClicked == playPauseButton)
    {
        playPauseButton->setToggleState(!(playPauseButton->getToggleState()), false);
    }
    else if(buttonThatWasClicked == stopButton)
    {
    
    }
    else if(buttonThatWasClicked == backwardButton)
    {
    
    }
    else if(buttonThatWasClicked == forwardButton)
    {
    
    }
    else if(buttonThatWasClicked == aboutButton)
    {
        showAboutUs();
    }
}

void GUI::ClientControlComponent::showAboutUs()
{
    // Show About Us Page and give the required information to users.
    AboutUsComponent aboutUsComponent;
    aboutUsComponent.setSize (300, 350);
    CsPlayerLookAndFeel csLnF;
    csLnF.setColour (Label::textColourId, Colours::white);
    csLnF.setColour (TextButton::buttonColourId, Colours::white);
    csLnF.setColour (TextButton::textColourOffId, Colours::black);
    csLnF.setColour (TextEditor::textColourId, Colours::grey);
    aboutUsComponent.setLookAndFeel(&csLnF);
    // Show the component inside dialog
    DialogWindow::showModalDialog ("About CsPlayer", &aboutUsComponent, nullptr, Colours::darkgrey, true, false, false);
}

void GUI::ClientControlComponent::setConfiguration()
{
    ClientSettingComponent clientSettingComponent(false);
    CsPlayerLookAndFeel csLnF;
    csLnF.setColour (Label::textColourId, Colours::white);
    csLnF.setColour (TextButton::buttonColourId, Colours::white);
    csLnF.setColour (TextButton::textColourOffId, Colours::black);
    csLnF.setColour (TextEditor::textColourId, Colours::grey);
    clientSettingComponent.setLookAndFeel(&csLnF);
    
    DialogWindow::showModalDialog ("Client Info", &clientSettingComponent, nullptr, Colours::darkgrey, true, false, false);
}