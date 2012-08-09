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

// Juce related definitions go here
#include "NetworkConnection.hpp"
// We need Configurations 
#include "../Common/Configurations.hpp"
// Ww need ClientSettingComponent
#include "../Components/PanelComponent/ClientSettingComponent.hpp"
// Ww need ClientSettingComponent
#include "../Components/PanelComponent/ClientControlComponent.hpp"

NetworkConnection::ClientConnection::ClientConnection() : 
ownerComponent(nullptr), settingComp(nullptr), controlComp(nullptr), alertWin(nullptr)
{
    LookAndFeel::getDefaultLookAndFeel().setColour (AlertWindow::backgroundColourId, Colours::darkgrey);
    LookAndFeel::getDefaultLookAndFeel().setColour (AlertWindow::textColourId,  Colours::white);
    LookAndFeel::getDefaultLookAndFeel().setColour (AlertWindow::outlineColourId, Colours::black);
    LookAndFeel::getDefaultLookAndFeel().setColour (TextButton::buttonColourId, Colours::black);
    LookAndFeel::getDefaultLookAndFeel().setColour (TextButton::textColourOnId, Colours::lightgrey);
    LookAndFeel::getDefaultLookAndFeel().setColour (TextButton::textColourOffId, Colours::white);
    alertWin = new AlertWindow("alert", "", AlertWindow::AlertIconType::WarningIcon);
}
NetworkConnection::ClientConnection::~ClientConnection()
{
}

void NetworkConnection::ClientConnection::setOwnerComponent(Component * ownerComp)
{
    ownerComponent = ownerComp;
    settingComp = dynamic_cast<GUI::ClientSettingComponent*> (ownerComponent);
    if(!settingComp)
    {
        controlComp = dynamic_cast<GUI::ClientControlComponent*> (ownerComponent);
        if(!controlComp)
            return;
    }
}

void NetworkConnection::ClientConnection::connectionMade()
{
    // When successfully connected :)
    String dataToSend;
    if(settingComp)
        dataToSend = messengerProtocol.constructFirstTimeName(settingComp->getClientName());
    else
    {
        if(controlComp)
            dataToSend = messengerProtocol.constructConnectTimeName(controlComp->getClientName());
    }
    MemoryBlock messageData(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(messageData);
}

void NetworkConnection::ClientConnection::connectionLost()
{
    // Stop the connected client
    if(settingComp)
    {
        settingComp->setClientAdded(true);
        settingComp->writeToXML();
        settingComp->getParentComponent()->setVisible(false);
        settingComp->getParentComponent()->exitModalState(1);
    }
    if(controlComp)
    {
        controlComp->setClientDisconnected();
    }
    disconnect();
}
bool NetworkConnection::ClientConnection::connectToServer(bool firstTime)
{
    if(firstTime)
    {
        if(settingComp)
        {
            bool serverResponse = connectToSocket(settingComp->getServerIPAddress(), settingComp->getPortNumber(), 1000);
            if(serverResponse)
                return true;
            else
                return false;
        }
        else
            return false;
    }
    else
    {
        if(controlComp)
        {
            bool serverResponse = connectToSocket(controlComp->getServerIPAddress(), controlComp->getPortNumber(), 1000);
            if(serverResponse)
                return true;
            else
            {
                alertWin->showMessageBox(AlertWindow::AlertIconType::WarningIcon, "Error", "Server not running / Incorrect details", "Ok", controlComp);
                return false;
            }
        }
        else
            return false;
    }
}

void NetworkConnection::ClientConnection::messageReceived (const MemoryBlock & message)
{
    String dataString;
    if(messageProtocols.isNoAccessMessage(message.toString(), dataString))
    {
        alertWin->showMessageBox(AlertWindow::AlertIconType::WarningIcon, "Error", dataString, "Ok", controlComp);
    }
    else if(messageProtocols.isPlayListMessage(message.toString(), dataString))
    {
        controlComp->getPlayListComponent()->updatePlayListFromServer(dataString);
    }
    else if(messageProtocols.isPlayingIndex(message.toString(), dataString))
    {
        controlComp->getPlayListComponent()->setPlayingSongIndex(dataString.getIntValue());
        controlComp->serverSentPlay();
    }
    else if(messageProtocols.isAllowLockMessage(message.toString()))
    {
        controlComp->manageLock(true);
    }
    else if(messageProtocols.isDenyLockMessage(message.toString()) || messageProtocols.isReleaseLockMessage(message.toString()))
    {
        controlComp->manageLock(false);
    }
    else if(messageProtocols.isServerIsLockedMessage(message.toString()))
    {
        controlComp->serverIsLocked(true);
    }
    else if(messageProtocols.isServerIsUnLockedMessage(message.toString()))
    {
        controlComp->serverIsLocked(true);
    }
	else if(messageProtocols.isAddInPlayList(message.toString(), dataString))
    {
        // add these songs in playList
        controlComp->getPlayListComponent()->addInPlayListFromServer(dataString);
    }
	else if(message.toString().contains(messageProtocols.getDeleteInPlayListID()))
    {
        Array<int> tempIndexList;
		messageProtocols.isDeleteInPlayList(message.toString(), tempIndexList);
		// delete these songs from playList
        controlComp->getPlayListComponent()->deleteInPlayListFromServer(tempIndexList);
    }
    else if(messageProtocols.isPlayMessage(message.toString()))
    {
        controlComp->serverSentPlay();
    }
    else if(messageProtocols.isStopMessage(message.toString()))
    {
        controlComp->serverSentStop();
    }
    else if(messageProtocols.isPauseMessage(message.toString()))
    {
        controlComp->serverSentPause();
    }

}

void NetworkConnection::ClientConnection::acquireLockOnServer()
{
    String dataToSend = messengerProtocol.constructAcquireLock();
    MemoryBlock message(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(message);
}

void NetworkConnection::ClientConnection::releaseLockOnServer()
{
    String dataToSend = messengerProtocol.constructReleaseLock();
    MemoryBlock message(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(message);
}

void NetworkConnection::ClientConnection::sendPlayAfterPauseToServer()
{
    /*Configurations::Protocols messengerProtocol;
    String dataToSend = messengerProtocol.constructReleaseLock();
    MemoryBlock message(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(message);*/
}

void NetworkConnection::ClientConnection::sendPlayToServer()
{
    String dataToSend = messengerProtocol.constructPlayMessage();
    MemoryBlock message(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(message);
}

void NetworkConnection::ClientConnection::sendPauseToServer()
{
    String dataToSend = messengerProtocol.constructPauseMessage();
    MemoryBlock message(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(message);
}

void NetworkConnection::ClientConnection::sendStopToServer()
{
    String dataToSend = messengerProtocol.constructStopMessage();
    MemoryBlock message(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(message);
}

void NetworkConnection::ClientConnection::sendBackToServer()
{
    String dataToSend = messengerProtocol.constructBackMessage();
    MemoryBlock message(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(message);
}

void NetworkConnection::ClientConnection::sendNextToServer()
{
    String dataToSend = messengerProtocol.constructNextMessage();
    MemoryBlock message(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(message);
}

void NetworkConnection::ClientConnection::songDoubleClickedPlay(const int index)
{
    String dataToSend = messengerProtocol.constructPlayAfterStopMessage(String(index));
    MemoryBlock message(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(message);
}

void NetworkConnection::ClientConnection::sendAddInPlayList(const String & playList)
{
    String dataToSend = messengerProtocol.constructAddInPlayList(playList);
    MemoryBlock message(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(message);
}

void NetworkConnection::ClientConnection::sendDeleteInPlayList(const Array<int> & indexList)
{
    String dataToSend = messengerProtocol.constructDeleteInPlayList(indexList);
    MemoryBlock message(dataToSend.toUTF8(), dataToSend.getNumBytesAsUTF8());
    sendMessage(message);
}