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
ownerComponent(nullptr), isFirstCall(true), settingComp(nullptr), controlComp(nullptr), alertWin(nullptr)
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
    Configurations::Protocols messengerProtocol;
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
    String messageToShow;
    if(messageProtocols.isNoAccessMessage(message.toString(), messageToShow))
    {
        alertWin->showMessageBox(AlertWindow::AlertIconType::WarningIcon, "Error", messageToShow, "Ok", controlComp);
    }
}

