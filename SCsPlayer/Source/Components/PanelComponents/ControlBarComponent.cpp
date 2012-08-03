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

// Control Bar definitions
#include "ControlBarComponent.hpp"
// AboutUs components
#include "AboutusComponent.hpp"
// LookAndFeel to set for scrollBar and other things
#include "../../Common/CsLookAndFeel.hpp"

#include "../MainComponent.hpp"

GUI::ControlBarComponent::ControlBarComponent(AudioDeviceManager & audioDeviceManager) :
audioDeviceManager(audioDeviceManager), audioDeviceSettingImageButton(nullptr), serverImageButton(nullptr),
aboutImageButton(nullptr), lockUnlockImageButton(nullptr), clockComp(nullptr), csServer(nullptr)
{
    addAndMakeVisible(audioDeviceSettingImageButton = new ImageButton("Audio Setting"));
    addAndMakeVisible(serverImageButton = new ImageButton("Server Setting"));
    addAndMakeVisible(lockUnlockImageButton = new ImageButton("Lock-Unlock Client"));
    addAndMakeVisible(aboutImageButton = new ImageButton("About us"));
    
    addAndMakeVisible(clockComp = new drow::Clock());

    Image img1, img2;

    img1 = ImageCache::getFromMemory(BinaryData::setting_gif, BinaryData::setting_gifSize);
    audioDeviceSettingImageButton->setImages(true, false, true, 
                                            img1, 1.0f, Colours::transparentBlack,
                                            img1, 0.7f, Colours::transparentBlack,
                                            img1, 1.0f, Colours::transparentBlack);
    audioDeviceSettingImageButton->addButtonListener(this);
    audioDeviceSettingImageButton->setToggleState(false, false);
    audioDeviceSettingImageButton->setTooltip("Audio Settings");
    img1 = ImageCache::getFromMemory(BinaryData::stopS_gif, BinaryData::stopS_gifSize);
    img2 = ImageCache::getFromMemory(BinaryData::startS_gif, BinaryData::startS_gifSize);
    serverImageButton->setImages (true, false, true, 
                                img1, 1.0f, Colours::transparentBlack,
                                img1, 0.7f, Colours::transparentBlack,
                                img2, 1.0f, Colours::transparentBlack);
    serverImageButton->addButtonListener(this);
    serverImageButton->setToggleState(false, false);
    serverImageButton->setTooltip("Start Server");
    img1 = ImageCache::getFromMemory(BinaryData::unlock_gif, BinaryData::unlock_gifSize);
    img2 = ImageCache::getFromMemory(BinaryData::lock_gif, BinaryData::lock_gifSize);
    lockUnlockImageButton->setImages (true, false, true, 
                                img1, 1.0f, Colours::transparentBlack,
                                img1, 0.7f, Colours::transparentBlack,
                                img2, 1.0f, Colours::transparentBlack);
    lockUnlockImageButton->addButtonListener(this);
    lockUnlockImageButton->setToggleState(false, false);
    lockUnlockImageButton->setTooltip("Allow Lock");
    img1 = ImageCache::getFromMemory(BinaryData::about_gif, BinaryData::about_gifSize);
    aboutImageButton->setImages(true, false, true, 
                                            img1, 1.0f, Colours::transparentBlack,
                                            img1, 0.7f, Colours::transparentBlack,
                                            img1, 1.0f, Colours::transparentBlack);
    aboutImageButton->addButtonListener(this);
    aboutImageButton->setToggleState(false, false);

    csServer = new NetworkConnection::ServerConnection(*this, lockUnlockImageButton->getToggleState());
}

GUI::ControlBarComponent::~ControlBarComponent()
{
    removeChildComponent(clockComp);
}

void GUI::ControlBarComponent::disconnectConnectedClient(const String & clientIpAddress)
{
    csServer->disconnectConnectedClient(clientIpAddress);
}

void GUI::ControlBarComponent::paint(Graphics & g)
{
    // backGround Filling
    g.fillAll (Colour (0xff292929));
    g.setColour(Colours::black);
    // to Drow the outline with black 
    g.drawRect (1.0f, 1.0f, (float)getWidth() - 2.0f, (float)getHeight() - 2.0f, 1.0f);
    // if needed here show locked status with Red and Green circle (Using eclipse)
}

void GUI::ControlBarComponent::resized()
{
    audioDeviceSettingImageButton->setBounds(proportionOfWidth(0.05f), proportionOfHeight(0.5f) - audioDeviceSettingImageButton->getHeight()/2, audioDeviceSettingImageButton->getWidth(), audioDeviceSettingImageButton->getHeight());
    serverImageButton->setBounds(proportionOfWidth(0.25f), proportionOfHeight(0.5f) - serverImageButton->getHeight()/2, serverImageButton->getWidth(), serverImageButton->getHeight());
    lockUnlockImageButton->setBounds(proportionOfWidth(0.45f), proportionOfHeight(0.5f) - lockUnlockImageButton->getHeight()/2, lockUnlockImageButton->getWidth(), lockUnlockImageButton->getHeight());
    aboutImageButton->setBounds(proportionOfWidth(0.65f), proportionOfHeight(0.5f) - aboutImageButton->getHeight()/2, aboutImageButton->getWidth(), aboutImageButton->getHeight());
    const int clockHeight = 20, clockWidth = 70;
    clockComp->setBounds(proportionOfWidth(0.80f), proportionOfHeight(0.5f) - clockHeight/2, clockWidth, clockHeight);
}

void GUI::ControlBarComponent::buttonClicked(Button * buttonThatWasClicked)
{
    // What happens when particular button is clicked ?
    if (buttonThatWasClicked == audioDeviceSettingImageButton) 
    {
        showAudioSettings();
    }
    else if (buttonThatWasClicked == serverImageButton) 
    {
        if(!serverImageButton->getToggleState())
        {
            // start the Ip server
            csServer->startServer();
            serverImageButton->setToggleState(true, false);
            Logger::outputDebugString("Cs Server is started");
            serverImageButton->setTooltip("Stop Server");
        }
        else
        {
            // stop the Ip server
            csServer->stopServer();
            serverImageButton->setToggleState(false, false);
            if(lockUnlockImageButton->getToggleState())
                lockUnlockImageButton->setToggleState(false, false);
            Logger::outputDebugString("Cs Server is stopped");
            serverImageButton->setTooltip("Start Server");
        }
    }
    else if(buttonThatWasClicked == lockUnlockImageButton)
    {
        // start
        if(lockUnlockImageButton->getToggleState())
        {
            csServer->releaseClientLock();
            lockUnlockImageButton->setToggleState(false,false);
            lockUnlockImageButton->setTooltip("Allow Lock");
        }
    }
    else if(buttonThatWasClicked == aboutImageButton)
    {
        showAboutUs();
    }
}

void GUI::ControlBarComponent::showAudioSettings()
{
    // Show Audio Setting Page and make audio settings done here.
    AudioDeviceSelectorComponent settingsComp (audioDeviceManager, 0, 2, 0, 2, true, true, true, false);
    settingsComp.setSize (300, 350);
    LookAndFeel settingsLaf;
    settingsLaf.setColour (Label::textColourId, Colours::white);
    settingsLaf.setColour (TextButton::buttonColourId, Colours::white);
    settingsLaf.setColour (TextButton::textColourOffId, Colours::black);
    settingsComp.setLookAndFeel (&settingsLaf);
    // Show the component inside dialog
    DialogWindow::showModalDialog ("Audio Settings", &settingsComp, nullptr, Colours::darkgrey, true, false, false);
}


void GUI::ControlBarComponent::showAboutUs()
{
    // Show About Us Page and give the required information to users.
    AboutUsComponent aboutUsComponent;
    aboutUsComponent.setSize (300, 350);
    CsLookAndFeel csLnF;
    csLnF.setColour (Label::textColourId, Colours::white);
    csLnF.setColour (TextButton::buttonColourId, Colours::white);
    csLnF.setColour (TextButton::textColourOffId, Colours::black);
    csLnF.setColour (TextEditor::textColourId, Colours::grey);
    aboutUsComponent.setLookAndFeel(&csLnF);
    // Show the component inside dialog
    DialogWindow::showModalDialog ("About CsPlayer", &aboutUsComponent, nullptr, Colours::darkgrey, true, false, false);
}

// Communication related methods 
bool GUI::ControlBarComponent::manageServerLock(const bool lock)
{   
    if(lock)
    {
        if(!lockUnlockImageButton->getToggleState())
        {
            lockUnlockImageButton->setToggleState(true,false);
            lockUnlockImageButton->setTooltip("Release Lock");
            return true;
        }    
        else
            return false;
    }
    else
    {
        lockUnlockImageButton->setToggleState(false,false);
        lockUnlockImageButton->setTooltip("Allow Lock");
        return true;
    }
}

GUI::ClientListComponent * GUI::ControlBarComponent::getClientListComponent()
{
    return findParentComponentOfClass<GUI::MainComponent>()->getLeftPanel()->getClientListComponent();
}

GUI::PlayListComponent * GUI::ControlBarComponent::getPlayListComponent()
{
    return findParentComponentOfClass<GUI::MainComponent>()->getRightPanel()->getPlayListComponent();
}

GUI::PlayerComponent * GUI::ControlBarComponent::getPlayerComponent()
{
    return findParentComponentOfClass<GUI::MainComponent>()->getCenterPanel()->getPlayerComponent();
}