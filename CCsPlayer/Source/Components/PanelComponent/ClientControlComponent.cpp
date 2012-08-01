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

GUI::ClientControlComponent::ClientControlComponent (): firstCall(true), connectImageButton(nullptr), settingImageButton(nullptr),
                                                        playPauseImageButton(nullptr), backwardImageButton(nullptr),
                                                        stopImageButton(nullptr), forwardImageButton(nullptr), aboutImageButton(nullptr),
                                                        clockComp(nullptr), mainElement(nullptr), lockUnlockImageButton(nullptr), isConnected(false)
{
    connector.setOwnerComponent(this);
    addAndMakeVisible (clockComp = new drow::Clock());

    addAndMakeVisible (connectImageButton = new ImageButton("connect"));
    addAndMakeVisible (settingImageButton = new ImageButton("setting"));
    addAndMakeVisible (lockUnlockImageButton = new ImageButton("lock unlock"));
    addAndMakeVisible (playPauseImageButton = new ImageButton("play pause"));
    addAndMakeVisible (backwardImageButton = new ImageButton("backward"));
    addAndMakeVisible (stopImageButton = new ImageButton("stop"));
    addAndMakeVisible (forwardImageButton = new ImageButton("forward"));
    addAndMakeVisible (aboutImageButton = new ImageButton("about"));
   
    Image img1, img2;
    // connect/disconnect
    img1 = ImageCache::getFromMemory(BinaryData::stopS_gif, BinaryData::stopS_gifSize);
    img2 = ImageCache::getFromMemory(BinaryData::startS_gif, BinaryData::startS_gifSize);
    connectImageButton->setToggleState(false, false);
    connectImageButton->setImages (true, false, true, 
                                img1, 1.0f, Colours::transparentBlack,
                                img1, 0.7f, Colours::transparentBlack,
                                img2, 1.0f, Colours::transparentBlack);
    connectImageButton->addButtonListener (this);

    // setting
    img1 = ImageCache::getFromMemory(BinaryData::setting_gif, BinaryData::setting_gifSize);
    settingImageButton->setImages(true, false, true,
                            img1, 1.0f, Colours::transparentBlack,
                            img1, 0.7f, Colours::transparentBlack,
                            img1, 1.0f, Colours::transparentBlack);
    settingImageButton->addButtonListener (this);

    // lock unlock
    img1 = ImageCache::getFromMemory(BinaryData::unlock_gif, BinaryData::unlock_gifSize);
    img2 = ImageCache::getFromMemory(BinaryData::lock_gif, BinaryData::lock_gifSize);
    lockUnlockImageButton->setToggleState(false, false);
    lockUnlockImageButton->setImages(true, false, true,
                            img1, 1.0f, Colours::transparentBlack,
                            img1, 0.7f, Colours::transparentBlack,
                            img2, 1.0f, Colours::transparentBlack);
    lockUnlockImageButton->addButtonListener (this);

    // backward
    img1 = ImageCache::getFromMemory(BinaryData::back_gif, BinaryData::back_gifSize);
    backwardImageButton->setImages(true, false, true,
                            img1, 1.0f, Colours::transparentBlack,
                            img1, 0.7f, Colours::transparentBlack,
                            img1, 1.0f, Colours::transparentBlack);
    backwardImageButton->addButtonListener (this);

    // play/pause
    img1 = ImageCache::getFromMemory(BinaryData::play_gif, BinaryData::play_gifSize);
    img2 = ImageCache::getFromMemory(BinaryData::pause_gif, BinaryData::pause_gifSize);
    playPauseImageButton->setToggleState(false, false);
    playPauseImageButton->setImages(true, false, true,
                            img1, 1.0f, Colours::transparentBlack,
                            img1, 0.7f, Colours::transparentBlack,
                            img2, 1.0f, Colours::transparentBlack);
    playPauseImageButton->addButtonListener (this);

    // stop
    img1 = ImageCache::getFromMemory(BinaryData::stop_gif, BinaryData::stop_gifSize);
    stopImageButton->setImages(true, false, true,
                            img1, 1.0f, Colours::transparentBlack,
                            img1, 0.7f, Colours::transparentBlack,
                            img1, 1.0f, Colours::transparentBlack);
    stopImageButton->addButtonListener (this);

    // forward
    img1 = ImageCache::getFromMemory(BinaryData::next_gif, BinaryData::next_gifSize);
    forwardImageButton->setImages(true, false, true,
                            img1, 1.0f, Colours::transparentBlack,
                            img1, 0.7f, Colours::transparentBlack,
                            img1, 1.0f, Colours::transparentBlack);
    forwardImageButton->addButtonListener (this);

    // about
    img1 = ImageCache::getFromMemory(BinaryData::about_gif, BinaryData::about_gifSize);
    aboutImageButton->setImages(true, false, true,
                            img1, 1.0f, Colours::transparentBlack,
                            img1, 0.7f, Colours::transparentBlack,
                            img1, 1.0f, Colours::transparentBlack);
    aboutImageButton->addButtonListener (this);

    // XML Reader
    XmlDocument mainDoc(File(File::getCurrentWorkingDirectory().getFullPathName() + File::separatorString + "csProp.xml"));
    mainElement = mainDoc.getDocumentElement();
    if(mainElement != 0)
    {
        XmlElement * tempEle;
        tempEle = mainElement->getFirstChildElement();
            
        setServerIpAddress(tempEle->getAllSubText());
        tempEle = tempEle->getNextElement();
        setPortNumber(tempEle->getAllSubText().getIntValue());
        tempEle = tempEle->getNextElement();
        setClientName(tempEle->getAllSubText());
    }
}
GUI::ClientControlComponent::~ClientControlComponent ()
{
    connectImageButton->removeButtonListener(this);
    settingImageButton->removeButtonListener(this);
    lockUnlockImageButton->removeButtonListener(this);
    backwardImageButton->removeButtonListener(this);
    playPauseImageButton->removeButtonListener(this);
    forwardImageButton->removeButtonListener(this);
    aboutImageButton->removeButtonListener(this);
    removeChildComponent(clockComp);
}
void GUI::ClientControlComponent::resized ()
{
    const int clockWidth = 80, clockHeight = 20;
    clockComp->setBounds(proportionOfWidth(0.5f) - clockWidth/2, proportionOfHeight(0.02f), clockWidth, clockHeight );
    connectImageButton->setBounds(proportionOfWidth(0.5f) - connectImageButton->getWidth()/2, proportionOfHeight(0.06f), connectImageButton->getWidth(), connectImageButton->getHeight());
    settingImageButton->setBounds(proportionOfWidth(0.5f) - settingImageButton->getWidth()/2, proportionOfHeight(0.16f), settingImageButton->getWidth(), settingImageButton->getHeight());
    lockUnlockImageButton->setBounds(proportionOfWidth(0.5f) -lockUnlockImageButton->getWidth()/2, proportionOfHeight(0.26f), lockUnlockImageButton->getWidth(), lockUnlockImageButton->getHeight());
    
    backwardImageButton->setBounds(proportionOfWidth(0.5f) - backwardImageButton->getWidth()/2, proportionOfHeight(0.40f), backwardImageButton->getWidth(), backwardImageButton->getHeight());
    playPauseImageButton->setBounds(proportionOfWidth(0.5f) - playPauseImageButton->getWidth()/2, proportionOfHeight(0.50f), playPauseImageButton->getWidth(), playPauseImageButton->getHeight());
    stopImageButton->setBounds(proportionOfWidth(0.5f) - stopImageButton->getWidth()/2, proportionOfHeight(0.60f), stopImageButton->getWidth(), stopImageButton->getHeight());
    forwardImageButton->setBounds(proportionOfWidth(0.5f) - forwardImageButton->getWidth()/2, proportionOfHeight(0.70f), forwardImageButton->getWidth(), forwardImageButton->getHeight());
    
    aboutImageButton->setBounds(proportionOfWidth(0.5f) - aboutImageButton->getWidth()/2, proportionOfHeight(0.85f), aboutImageButton->getWidth(), aboutImageButton->getHeight());
}
void GUI::ClientControlComponent::paint (Graphics & g)
{
      g.fillAll (Colour (0xff292929));
}

void GUI::ClientControlComponent::buttonClicked (Button* buttonThatWasClicked)
{
     if(buttonThatWasClicked == connectImageButton)
    {   
        // Currently show no busy wheel please
        // findParentComponentOfClass<GUI::MainComponent>()->getRightPanel()->activeBusyWheel();
        if(!connectImageButton->getToggleState())
        {
            isConnected = connector.connectToServer(false);
            if(!isConnected)
                connector.disconnect();
            else
                connectImageButton->setToggleState(true, false);
        }
        else
        {
            connector.disconnect();
            connectImageButton->setToggleState(false, false);
        }
            
    }
    else if(buttonThatWasClicked == settingImageButton)
    {
        setConfiguration();        
    }
    else if(buttonThatWasClicked == lockUnlockImageButton)
    {
        if(!lockUnlockImageButton->getToggleState())
        {
            if(isConnected)
            {
                connector.aquireLockOnServer();
            }
        }
        else
        {
            connector.releaseLockOnServer();
            lockUnlockImageButton->setToggleState(false, false);
        }
    }
    else if(buttonThatWasClicked == playPauseImageButton)
    {
        playPauseImageButton->setToggleState(!(playPauseImageButton->getToggleState()), false);
    }
    else if(buttonThatWasClicked == stopImageButton)
    {
    
    }
    else if(buttonThatWasClicked == backwardImageButton)
    {
    
    }
    else if(buttonThatWasClicked == forwardImageButton)
    {
    
    }
    else if(buttonThatWasClicked == aboutImageButton)
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
    ClientSettingComponent clientSettingComponent(false, this);

    CsPlayerLookAndFeel csLnF;
    csLnF.setColour (Label::textColourId, Colours::white);
    csLnF.setColour (TextButton::buttonColourId, Colours::white);
    csLnF.setColour (TextButton::textColourOffId, Colours::black);
    csLnF.setColour (TextEditor::textColourId, Colours::grey);
    clientSettingComponent.setLookAndFeel(&csLnF);
    
    DialogWindow::showModalDialog ("Client Info", &clientSettingComponent, nullptr, Colours::darkgrey, true, false, false);
}

GUI::PlayListComponent * GUI::ClientControlComponent::getPlayListComponent()
{
    return findParentComponentOfClass<GUI::MainComponent>()->getRightPanel()->getPlayListComponent();
}

void GUI::ClientControlComponent::manageLock(bool lockGranted)
{
    lockUnlockImageButton->setToggleState(lockGranted, false);
}