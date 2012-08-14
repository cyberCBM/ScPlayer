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
// We need main component that hold other components
#include "../MainComponent.hpp"
// We need playList component to manage playing list
#include "PlayListComponent.hpp"

GUI::ClientControlComponent::ClientControlComponent (): firstCall(true), connectImageButton(nullptr), settingImageButton(nullptr),
    playPauseImageButton(nullptr), backwardImageButton(nullptr),
    stopImageButton(nullptr), forwardImageButton(nullptr), aboutImageButton(nullptr),
    clockComp(nullptr), mainElement(nullptr), lockUnlockImageButton(nullptr), isConnected(false), 
    serverLocked(false), ServerLockImageButton(nullptr), songStopped(true)
{
    connector.setOwnerComponent(this);
    addAndMakeVisible (clockComp = new ClockComponent());

    addAndMakeVisible (connectImageButton = new ImageButton("connect"));
    addAndMakeVisible (settingImageButton = new ImageButton("setting"));
    addAndMakeVisible (lockUnlockImageButton = new ImageButton("lock unlock"));
    addAndMakeVisible (playPauseImageButton = new ImageButton("play pause"));
    addAndMakeVisible (backwardImageButton = new ImageButton("backward"));
    addAndMakeVisible (stopImageButton = new ImageButton("stop"));
    addAndMakeVisible (forwardImageButton = new ImageButton("forward"));
    addAndMakeVisible (aboutImageButton = new ImageButton("about"));
    addAndMakeVisible (ServerLockImageButton = new ImageButton("about"));

    Image img1, img2;
    // connect/disconnect
    img1 = ImageCache::getFromMemory(BinaryData::stopS_gif, BinaryData::stopS_gifSize);
    img2 = ImageCache::getFromMemory(BinaryData::startS_gif, BinaryData::startS_gifSize);
    connectImageButton->setToggleState(false, false);
    connectImageButton->setImages (true, false, true, 
        img1, 1.0f, Colours::transparentBlack,
        img1, 0.7f, Colours::transparentBlack,
        img2, 1.0f, Colours::transparentBlack);
    connectImageButton->setTooltip("Connect to Server");
    connectImageButton->addButtonListener (this);

    // setting
    img1 = ImageCache::getFromMemory(BinaryData::setting_gif, BinaryData::setting_gifSize);
    settingImageButton->setImages(true, false, true,
        img1, 1.0f, Colours::transparentBlack,
        img1, 0.7f, Colours::transparentBlack,
        img1, 1.0f, Colours::transparentBlack);
    settingImageButton->setTooltip("Client's Settings");
    settingImageButton->addButtonListener (this);

    // lock unlock
    img1 = ImageCache::getFromMemory(BinaryData::unlock_gif, BinaryData::unlock_gifSize);
    img2 = ImageCache::getFromMemory(BinaryData::lock_gif, BinaryData::lock_gifSize);
    lockUnlockImageButton->setToggleState(false, false);
    lockUnlockImageButton->setImages(true, false, true,
        img1, 1.0f, Colours::transparentBlack,
        img1, 0.7f, Colours::transparentBlack,
        img2, 1.0f, Colours::transparentBlack);
    lockUnlockImageButton->setTooltip("Lock Server");
    lockUnlockImageButton->addButtonListener (this);

    // backward
    img1 = ImageCache::getFromMemory(BinaryData::back_gif, BinaryData::back_gifSize);
    backwardImageButton->setImages(true, false, true,
        img1, 1.0f, Colours::transparentBlack,
        img1, 0.7f, Colours::transparentBlack,
        img1, 1.0f, Colours::transparentBlack);
    backwardImageButton->setTooltip("Previous");
    backwardImageButton->addButtonListener (this);
    backwardImageButton->setEnabled(false);

    // play/pause
    img1 = ImageCache::getFromMemory(BinaryData::play_gif, BinaryData::play_gifSize);
    img2 = ImageCache::getFromMemory(BinaryData::pause_gif, BinaryData::pause_gifSize);
    playPauseImageButton->setToggleState(false, false);
    playPauseImageButton->setImages(true, false, true,
        img1, 1.0f, Colours::transparentBlack,
        img1, 0.7f, Colours::transparentBlack,
        img2, 1.0f, Colours::transparentBlack);
    playPauseImageButton->setTooltip("Play/pause");
    playPauseImageButton->addButtonListener (this);
    playPauseImageButton->setEnabled(false);

    // stop
    img1 = ImageCache::getFromMemory(BinaryData::stop_gif, BinaryData::stop_gifSize);
    stopImageButton->setImages(true, false, true,
        img1, 1.0f, Colours::transparentBlack,
        img1, 0.7f, Colours::transparentBlack,
        img1, 1.0f, Colours::transparentBlack);
    stopImageButton->setTooltip("Stop");
    stopImageButton->addButtonListener (this);
    stopImageButton->setEnabled(false);

    // forward
    img1 = ImageCache::getFromMemory(BinaryData::next_gif, BinaryData::next_gifSize);
    forwardImageButton->setImages(true, false, true,
        img1, 1.0f, Colours::transparentBlack,
        img1, 0.7f, Colours::transparentBlack,
        img1, 1.0f, Colours::transparentBlack);
    forwardImageButton->setTooltip("Next");
    forwardImageButton->addButtonListener (this);
    forwardImageButton->setEnabled(false);

    // about
    img1 = ImageCache::getFromMemory(BinaryData::about_gif, BinaryData::about_gifSize);
    aboutImageButton->setImages(true, false, true,
        img1, 1.0f, Colours::transparentBlack,
        img1, 0.7f, Colours::transparentBlack,
        img1, 1.0f, Colours::transparentBlack);
    aboutImageButton->setTooltip("About CsPlayer");
    aboutImageButton->addButtonListener (this);

    img1 = ImageCache::getFromMemory(BinaryData::connect_gif, BinaryData::connect_gifSize);
    img2 = ImageCache::getFromMemory(BinaryData::disconnect_gif, BinaryData::disconnect_gifSize);
    ServerLockImageButton->setToggleState(false, false);
    ServerLockImageButton->setTooltip("Server is not locked");
    ServerLockImageButton->setImages(true, false, true,
        img1, 1.0f, Colours::transparentBlack,
        img1, 0.7f, Colours::transparentBlack,
        img2, 1.0f, Colours::transparentBlack);

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

    aboutImageButton->setBounds(proportionOfWidth(0.5f) - aboutImageButton->getWidth()/2, proportionOfHeight(0.80f), aboutImageButton->getWidth(), aboutImageButton->getHeight());
    ServerLockImageButton->setBounds(proportionOfWidth(0.5f) - ServerLockImageButton->getWidth()/2, proportionOfHeight(0.90f), ServerLockImageButton->getWidth(), ServerLockImageButton->getHeight());
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
            isConnected = false;
            if(lockUnlockImageButton->getToggleState())
            {
                connector.releaseLockOnServer();
                manageLock(false);
            }
            connectImageButton->setToggleState(false, false);
            connector.disconnect();
        }

    }
    else if(buttonThatWasClicked == settingImageButton)
    {
        showSettingComponent();        
    }
    else if(buttonThatWasClicked == lockUnlockImageButton)
    {
		if(!lockUnlockImageButton->getToggleState())
        {
			if(ServerLockImageButton->getToggleState())
				return;
            if(isConnected)
            {
                connector.acquireLockOnServer();
            }
        }
        else
        {
            connector.releaseLockOnServer();
            manageLock(false);
        }
    }
    else if(buttonThatWasClicked == playPauseImageButton)
    {
        // It shows that i have lock on server and I can send modifications to server
        if(playPauseImageButton->getToggleState())
        {
            songStopped = false ;
            // Current is playing state
            connector.sendPauseToServer();
            playPauseImageButton->setToggleState(false,false);
        }
        else
        {
            if(!songStopped)
            {
                // Current is pause state
                connector.sendPlayToServer();
                playPauseImageButton->setToggleState(true,false);
            }
            else
            {
                connector.songDoubleClickedPlay(getPlayListComponent()->getCurrentSelectedIndex());
            }
        }
        //playPauseImageButton->setToggleState(!(playPauseImageButton->getToggleState()), false);
    }
    else if(buttonThatWasClicked == stopImageButton)
    {
        songStopped = true;
        // It shows that i have lock on server and I can send modifications to server
        playPauseImageButton->setToggleState(false, false);
        connector.sendStopToServer();
    }
    else if(buttonThatWasClicked == backwardImageButton)
    {
        // It shows that i have lock on server and I can send modifications to server
        connector.sendBackToServer();
    }
    else if(buttonThatWasClicked == forwardImageButton)
    {
        // It shows that i have lock on server and I can send modifications to server
        connector.sendNextToServer();
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

void GUI::ClientControlComponent::showSettingComponent()
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

void GUI::ClientControlComponent::setClientDisconnected()
{
    isConnected = false;
    if(lockUnlockImageButton->getToggleState())
    {
        connector.releaseLockOnServer();
        manageLock(false);
    }
    connectImageButton->setToggleState(false, false);
    // Because when client is offline it can change own thing at it's own
    getPlayListComponent()->allowPlayListModification(true);
}

void GUI::ClientControlComponent::manageLock(bool lockGranted)
{
    lockUnlockImageButton->setToggleState(lockGranted, false);
    if(lockGranted)
    {
        serverLocked = true;
        playPauseImageButton->setEnabled(true);
        stopImageButton->setEnabled(true);
        backwardImageButton->setEnabled(true);
        forwardImageButton->setEnabled(true);
        ServerLockImageButton->setToggleState(true, false);
        getPlayListComponent()->allowPlayListModification(true);
    }
    else
    {
        serverLocked = false;
        playPauseImageButton->setEnabled(false);
        stopImageButton->setEnabled(false);
        backwardImageButton->setEnabled(false);
        forwardImageButton->setEnabled(false);
        ServerLockImageButton->setToggleState(false, false);
        getPlayListComponent()->allowPlayListModification(false);
    }
}

void GUI::ClientControlComponent::serverIsLocked(bool locked)
{
    if(locked)
        ServerLockImageButton->setToggleState(true, false);
    else
        ServerLockImageButton->setToggleState(false, false);
}

void GUI::ClientControlComponent::songDoubleClickedPlay(const int index)
{
    if(serverLocked)
    {
        playPauseImageButton->setToggleState(true, false);
        connector.songDoubleClickedPlay(index);
    }
}

void GUI::ClientControlComponent::addInPlayListToServer(const String & playList)
{
    if(serverLocked)
        connector.sendAddInPlayList(playList);
}

void GUI::ClientControlComponent::deleteInPlayListToServer(const Array<int> & indexList)
{
    if(serverLocked)
        connector.sendDeleteInPlayList(indexList);
}

void GUI::ClientControlComponent::sendStopToServer()
{
    if(serverLocked)
        stopImageButton->triggerClick();
}

void GUI::ClientControlComponent::serverSentStop()
{
    playPauseImageButton->setToggleState(false, false);
    songStopped = true;
}
void GUI::ClientControlComponent::serverSentPause()
{
    songStopped = false;
    playPauseImageButton->setToggleState(false, false);
}

void GUI::ClientControlComponent::serverSentPlay()
{
    playPauseImageButton->setToggleState(true, false);
    songStopped = false;
}